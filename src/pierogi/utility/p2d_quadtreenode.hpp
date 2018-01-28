#ifndef P2D_QUADTREENODE_HPP
#define P2D_QUADTREENODE_HPP

#include <vector>
#include <memory>
#include <string>

#include "SDL.h"
#include "p2d_rect.hpp"

#include "p2d_stringutils.hpp"

#include "../p2d_object.hpp"
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
    template <uint N>
    class QuadTreeNode {
    public:
        QuadTreeNode(const SubQuad& quadHeading, const Rect<float>& rectCoverage);
        ~QuadTreeNode();
        void subdivide();
        bool isLeafNode() const;

        void insert(p2d::Object* obj);
        void insert(p2d::Object& obj);

        void setRectCoverage(const Rect<float>& rect);
        bool coversPoint(const p2d::math::Vector2f& point) const;

        QuadTreeNode* findNodeContaining(const p2d::math::Vector2f& point);
        std::vector<p2d::Object*> containedObjects();

        QuadTreeNode& operator[] (const SubQuad& which);

        void draw(SDL_Renderer* renderer) const;

    protected:
        void setParent(QuadTreeNode* newParentPtr);
        void setHeading(const SubQuad& heading);
    private:
        bool isLeafNode_ = true;
        uint treeDepth = 0;
        const unsigned int capacity;
        std::vector<p2d::Object*> container;
        Rect<float> coverage;
        QuadTreeNode* parentPtr = nullptr;
        QuadTreeNode* quadNW;
        QuadTreeNode* quadSW;
        QuadTreeNode* quadNE;
        QuadTreeNode* quadSE;
        SubQuad heading;

        void distributeRectCoverageToSubnodes();
        void setParentOfSubnodes();
        void setSubnodeHeading();
        void setDepth(uint depth = 0);
        void distributeObjectsToSubnodes();

        p2d::debug::Logger* logger;
    }; // QuadTreeTree

    template <uint N>
    QuadTreeNode<N>::QuadTreeNode(const SubQuad& quadHeading, const Rect<float>& rectCoverage)
    : capacity(N), heading(quadHeading), coverage(rectCoverage) {
        logger = p2d::debug::Logger::getInstancePtr();
        container.reserve(4);
        //logger->log("QuadTreeNode constructed...", p2d::debug::LogLevel::DEBUG);
    } // constructor

    template <uint N>
    QuadTreeNode<N>::~QuadTreeNode() {
        delete quadNW;
        delete quadSW;
        delete quadNE;
        delete quadSE;
        // Memory access error when deleting
    }

    template <uint N>
    void QuadTreeNode<N>::subdivide() {
        std::cout << "\t Subdividing lead node into quadtreenodes at ";
        if (isLeafNode()) {
            Rect<float> newCoverage = coverage * 0.5f;
            quadNW = new QuadTreeNode<N>(SubQuad::NW, newCoverage);
            quadSW = new QuadTreeNode<N>(SubQuad::SW, newCoverage + newCoverage.getSize().getVectorY());
            quadNE = new QuadTreeNode<N>(SubQuad::NE, newCoverage + newCoverage.getSize().getVectorX());
            quadSE = new QuadTreeNode<N>(SubQuad::SE, newCoverage + newCoverage.getSize());
            std::cout << quadNW << ", " << quadSW << ", " << quadNE << ", " << quadSE << std::endl;
            isLeafNode_ = false;
            setParentOfSubnodes();
            setDepth();
            distributeObjectsToSubnodes();
        } // if
    } // subdivide

    template <uint N>
    bool QuadTreeNode<N>::isLeafNode() const {
        return isLeafNode_;
    } // subdivide

    template <uint N>
    void QuadTreeNode<N>::insert(p2d::Object* objPtr) {
        if (isLeafNode()) {
            if (container.size() < capacity) {
                std::cout << "Inserting object at " << objPtr << " into leaf node " << this << std::endl;
                container.push_back(objPtr);
            } else {
                std::cout << "Container capacity reached. Time for S U B D I V I S I O N" << std::endl;
                subdivide();
            } // if else
        } else {
            findNodeContaining(objPtr->getPosition())->insert(objPtr);
        } // if else
    } // insert

    template <uint N>
    void QuadTreeNode<N>::insert(p2d::Object& obj) {
        insert(&obj);
    } // insert

    template <uint N>
    void QuadTreeNode<N>::setParent(QuadTreeNode* newParentPtr) {
        parentPtr = newParentPtr;
    } // subdivide

    template <uint N>
    void QuadTreeNode<N>::setHeading(const SubQuad& subnodeHeading) {
        heading = subnodeHeading;
    } // subdivide

    template <uint N>
    void QuadTreeNode<N>::setRectCoverage(const Rect<float>& rect) {
        coverage = rect;
    } // setRectCoverage

    template <uint N>
    bool QuadTreeNode<N>::coversPoint(const p2d::math::Vector2f& point) const {
        return coverage.contains(point);
    } // coversPoint

    template <uint N>
    QuadTreeNode<N>* QuadTreeNode<N>::findNodeContaining(const p2d::math::Vector2f& point) {
        if (quadNW->coversPoint(point)) {
            if (quadNW->isLeafNode()) {
                return quadNW;
            } else {
                return quadNW->findNodeContaining(point);
            } // if else
        } // if
        if (quadSW->coversPoint(point)) {
            if (quadSW->isLeafNode()) {
                return quadSW;
            } else {
                return quadSW->findNodeContaining(point);
            } // if else
        } // if
        if (quadNE->coversPoint(point)) {
            if (quadNE->isLeafNode()) {
                return quadNE;
            } else {
                return quadNE->findNodeContaining(point);
            } // if else
        } // if
        if (quadSE->coversPoint(point)) {
            if (quadSE->isLeafNode()) {
                return quadSE;
            } else {
                return quadSE->findNodeContaining(point);
            } // if else
        } // if
        return this;
    } // findNodeContaining

    template <uint N>
    std::vector<p2d::Object*> QuadTreeNode<N>::containedObjects() {
        if (isLeafNode()) {
            return container;
        } else {
            std::vector<p2d::Object*> result;
            for (uint i = 0; i < 4; i++) {
                std::vector<p2d::Object*> collected = subnodes[i].containedObjects();
                result.insert(result.end(), collected.begin(), collected.end());
            } // for
            return result;
        } // if else
    } // containedObjects

    template <uint N>
    QuadTreeNode<N>& QuadTreeNode<N>::operator[] (const SubQuad& which) {
        return subnodes[static_cast<uint>(which)];
    } // operator []

    template <uint N>
    void QuadTreeNode<N>::setParentOfSubnodes() {
        quadNW->setParent(this);
        quadSW->setParent(this);
        quadNE->setParent(this);
        quadSE->setParent(this);
    } // distributeRectCoverageToSubnodes

    template <uint N>
    void QuadTreeNode<N>::setDepth(uint depth) {
        treeDepth = depth;
        if (!isLeafNode()) {
            quadNW->setDepth(treeDepth + 1);
            quadSW->setDepth(treeDepth + 1);
            quadNE->setDepth(treeDepth + 1);
            quadSE->setDepth(treeDepth + 1);
        } // if 
    } // setDepth

    template <uint N>
    void QuadTreeNode<N>::distributeObjectsToSubnodes() {
        std::cout << container.size() << std::endl;
        for (p2d::Object* objPtr : container) {
            findNodeContaining(objPtr->getPosition())->insert(objPtr);
        } // for
        container.clear();
        std::cout << container.size() << std::endl;
    } // distributePObjectsToSubnodes

    template <uint N>
    void QuadTreeNode<N>::draw(SDL_Renderer* renderer) const {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &coverage.getSDLRect());
        if (!isLeafNode()) {
            quadNW->draw(renderer);
            quadSW->draw(renderer);
            quadNE->draw(renderer);
            quadSE->draw(renderer);
        } // if
    } // draw
} // utility
} // p2d

#endif