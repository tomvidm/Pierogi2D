#ifndef P2D_QUADTREE_HPP
#define P2D_QUADTREE_HPP

#include <vector>
#include <memory>

#include "p2d_rect.hpp"

#include "../debug/p2d_logger.hpp"

namespace p2d { namespace utility {
    typedef unsigned int IntMask;
    typedef unsigned int uint;

    enum SubQuad { 
        NW = 0, 
        NE = 1, 
        SE = 2, 
        SW = 3 
    };

    /*
    QuadTreeNode
    Holds N objects of type T and some info about its place in the quadtree.
    */
    template <typename T, uint N>
    class QuadTreeNode {
    public:
        QuadTreeNode();
        void subdivide();
        bool isLeafNode() const;

        void setRectCoverage(const Rect<float>& rect);
        bool coversPoint(const p2d::math::Vector2f& point) const;

        QuadTreeNode& operator[] (const SubQuad& which);
    protected:
        void setParent(QuadTreeNode* newParentPtr);
    private:
        bool isLeafNode_ = true;
        const unsigned int capacity;
        Rect<float> coverage;
        QuadTreeNode* subnodes;
        QuadTreeNode* parentPtr = nullptr;

        void distributeRectCoverageToSubnodes();
        void setParentOfSubnodes();

        p2d::debug::Logger* logger;
    }; // QuadTreeTree

    template <typename T, uint N>
    QuadTreeNode<T, N>::QuadTreeNode()
    : capacity(N) {
        logger = p2d::debug::Logger::getInstancePtr();
        logger->log("QuadTreeNode constructed...", p2d::debug::LogLevel::DEBUG);
    } // constructor

    template <typename T, uint N>
    void QuadTreeNode<T, N>::subdivide() {
        if (isLeafNode()) {
            logger->log("Splitting quadtree...", p2d::debug::LogLevel::DEBUG);
            subnodes = new QuadTreeNode<T, N>[4];
            isLeafNode_ = false;
            distributeRectCoverageToSubnodes();
            setParentOfSubnodes();
        } else {
            logger->log("Already split...", p2d::debug::LogLevel::DEBUG);
        }
        
    } // subdivide

    template <typename T, uint N>
    bool QuadTreeNode<T, N>::isLeafNode() const {
        return isLeafNode_;
    } // subdivide

    template <typename T, uint N>
    void QuadTreeNode<T, N>::setParent(QuadTreeNode* newParentPtr) {
        parentPtr = newParentPtr;
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
} // utility
} // p2d

#endif