#ifndef P2D_QUADTREE_HPP
#define P2D_QUADTREE_HPP

#include <vector>
#include <memory>
#include <string>

#include "p2d_rect.hpp"

#include "p2d_stringutils.hpp"

#include "../debug/p2d_logger.hpp"

namespace p2d { namespace utility {
    typedef unsigned int IntMask;
    typedef unsigned int uint;

    enum SubQuad { 
        ROOT = -1,
        NW = 0, 
        NE = 1, 
        SE = 2, 
        SW = 3
    };

    /*
    QuadTreeNode
    Holds N objects of type T and some info about its place in the quadtree.

    REQUIRES:
    The container holds pointers to objects of type T. For the algorithms to work,
    T must have an interface which 
    */
    template <typename T, uint N>
    class QuadTreeNode {
    public:
        QuadTreeNode();
        void subdivide();
        bool isLeafNode() const;

        void insert(T& obj);

        void setRectCoverage(const Rect<float>& rect);
        bool coversPoint(const p2d::math::Vector2f& point) const;

        QuadTreeNode& findNodeContaining(const p2d::math::Vector2f& point);
        std::vector<T*> containedObjects();

        QuadTreeNode& operator[] (const SubQuad& which);

        std::string generateDebugString() const;
    protected:
        void setParent(QuadTreeNode* newParentPtr);
        void setHeading(const SubQuad& heading);
    private:
        bool isLeafNode_ = true;
        uint treeDepth = 0;
        const unsigned int capacity;
        std::vector<T*> container;
        Rect<float> coverage;
        QuadTreeNode* subnodes;
        QuadTreeNode* parentPtr = nullptr;
        SubQuad heading;

        void distributeRectCoverageToSubnodes();
        void setParentOfSubnodes();
        void setSubnodeHeading();
        void updateDepths();
        void setDepth(uint depth = 0);
        void distributeObjectsToSubnodes();

        p2d::debug::Logger* logger;
    }; // QuadTreeTree

    template <typename T, uint N>
    QuadTreeNode<T, N>::QuadTreeNode()
    : capacity(N), heading(SubQuad::ROOT) {
        logger = p2d::debug::Logger::getInstancePtr();
        //logger->log("QuadTreeNode constructed...", p2d::debug::LogLevel::DEBUG);
    } // constructor

    template <typename T, uint N>
    void QuadTreeNode<T, N>::subdivide() {
        if (isLeafNode()) {
            logger->log("Splitting leaf node...", p2d::debug::LogLevel::DEBUG);
            subnodes = new QuadTreeNode<T, N>[4];
            isLeafNode_ = false;
            distributeRectCoverageToSubnodes();
            setParentOfSubnodes();
            setSubnodeHeading();
            updateDepths();
        } else {
            //logger->log("Already split...", p2d::debug::LogLevel::DEBUG);
            ;
        }
    } // subdivide

    template <typename T, uint N>
    bool QuadTreeNode<T, N>::isLeafNode() const {
        return isLeafNode_;
    } // subdivide

    template <typename T, uint N>
    void QuadTreeNode<T, N>::insert(T& obj) {
        if (container.size() < capacity) {
            logger->log("Inserting object at leaf...", p2d::debug::LogLevel::DEBUG);
            container.push_back(&obj);
        } else {
            logger->log("Subdividing to find place for object...", p2d::debug::LogLevel::DEBUG);
            subdivide();
            distributeObjectsToSubnodes();
            findNodeContaining(obj.getPosition()).insert(obj);
        } // if else
    } // insert

    template <typename T, uint N>
    void QuadTreeNode<T, N>::setParent(QuadTreeNode* newParentPtr) {
        parentPtr = newParentPtr;
    } // subdivide

    template <typename T, uint N>
    void QuadTreeNode<T, N>::setHeading(const SubQuad& subnodeHeading) {
        heading = subnodeHeading;
    } // subdivide

    template <typename T, uint N>
    void QuadTreeNode<T, N>::setRectCoverage(const Rect<float>& rect) {
        coverage = rect;
    } // setRectCoverage

    template <typename T, uint N>
    bool QuadTreeNode<T, N>::coversPoint(const p2d::math::Vector2f& point) const {
        return coverage.contains(point);
    } // coversPoint

    template <typename T, uint N>
    QuadTreeNode<T, N>& QuadTreeNode<T, N>::findNodeContaining(const p2d::math::Vector2f& point) {
        for (unsigned int i = 0; i < 4; i++) {
            if (subnodes[i].coversPoint(point)) {
                if (subnodes[i].isLeafNode()) {
                    return subnodes[i];
                } else {
                    return subnodes[i].findNodeContaining(point);
                } // if
            } // if
        } // for
        return *this;
    } // findNodeContaining

    template <typename T, uint N>
    std::vector<T*> QuadTreeNode<T, N>::containedObjects() {
        if (isLeafNode()) {
            return container;
        } else {
            std::vector<T*> result;
            for (uint i = 0; i < 4; i++) {
                std::vector<T*> collected = subnodes[i].containedObjects();
                result.insert(result.end(), collected.begin(), collected.end());
            } // for
            return result;
        } // if else
    } // containedObjects

    template <typename T, uint N>
    QuadTreeNode<T, N>& QuadTreeNode<T, N>::operator[] (const SubQuad& which) {
        return subnodes[static_cast<uint>(which)];
    } // operator []

    template <typename T, uint N>
    void QuadTreeNode<T, N>::distributeRectCoverageToSubnodes() {
        Rect<float> newCoverage = coverage * 0.5f;
        subnodes[0].setRectCoverage(newCoverage);
        subnodes[1].setRectCoverage(newCoverage + newCoverage.getSize().getVectorX());
        subnodes[2].setRectCoverage(newCoverage + newCoverage.getSize());
        subnodes[3].setRectCoverage(newCoverage + newCoverage.getSize().getVectorY());
    } // distributeRectCoverageToSubnodes

    template <typename T, uint N>
    void QuadTreeNode<T, N>::setParentOfSubnodes() {
        subnodes[0].setParent(this);
        subnodes[1].setParent(this);
        subnodes[2].setParent(this);
        subnodes[3].setParent(this);
    } // distributeRectCoverageToSubnodes

    template <typename T, uint N>
    void QuadTreeNode<T, N>::setSubnodeHeading() {
        subnodes[0].setHeading(SubQuad::NW);
        subnodes[1].setHeading(SubQuad::NE);
        subnodes[2].setHeading(SubQuad::SE);
        subnodes[3].setHeading(SubQuad::SW);
    } // distributeRectCoverageToSubnodes

    template <typename T, uint N>
    void QuadTreeNode<T, N>::updateDepths() {
        for (uint i = 0; i < 4; i++) {
            subnodes[i].setDepth(treeDepth + 1);
        }
    }

    template <typename T, uint N>
    void QuadTreeNode<T, N>::setDepth(uint depth) {
        treeDepth = depth;
        if (!isLeafNode()) {
            for (uint i = 0; i < 4; i++) {
                subnodes[i].setDepth(treeDepth + 1);
            }// for
        } // if 
    } // setDepth

    template <typename T, uint N>
    void QuadTreeNode<T, N>::distributeObjectsToSubnodes() {
        for (auto objPtr : container) {
            findNodeContaining(objPtr->getPosition()).insert(*objPtr);
        } // for
        container.clear();
    }

    template <typename T, uint N>
    std::string QuadTreeNode<T, N>::generateDebugString() const {
        std::string str = ntabs(treeDepth);
        str = str + "* Node\n" + 
                     ntabs(treeDepth) + "| Objects = " + std::to_string(container.size()) + "\n";
        if (!isLeafNode()) {
            for (uint i = 0; i < 4; i++) {
                str = str + subnodes[i].generateDebugString();
            } // for
        } // if
        return str; 
    } // generateDebugString
} // utility
} // p2d

#endif