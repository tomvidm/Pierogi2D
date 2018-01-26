#ifndef P2D_QUADTREE_HPP
#define P2D_QUADTREE_HPP

#include <vector>

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

        QuadTreeNode& operator[] (const SubQuad& which);
    private:
        const unsigned int capacity;

        bool isLeafNode_ = true;
        QuadTreeNode* subnodes;

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
        } else {
            logger->log("Already split...", p2d::debug::LogLevel::DEBUG);
        }
        
    } // subdivide

    template <typename T, uint N>
    bool QuadTreeNode<T, N>::isLeafNode() const {
        return isLeafNode_;
    } // subdivide

    template <typename T, uint N>
    QuadTreeNode<T, N>& QuadTreeNode<T, N>::operator[] (const SubQuad& which) {
        return subnodes[static_cast<uint>(which)];
    } // operator []
} // utility
} // p2d

#endif