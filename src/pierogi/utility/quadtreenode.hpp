#ifndef QUADTREENODE_HPP
#define QUADTREENODE_HPP

#include <memory>
#include <vector>
#include <string>

#include "p2d_rect.hpp"

#define NUM_SUBQUADS 4

namespace p2d { namespace utility {
    typedef unsigned int uint;

    template <typename T>
    class QuadTreeNode {
    public:
        QuadTreeNode(const p2d::utility::Rect<float>& quadCoverage);
    private:
        Rect<float> coverage;
        QuadTreeNode<T>* parentPtr;
        std::unique_ptr<QuadTreeNode<T>> subnodes[NUM_SUBQUADS];
        std::vector<std::shared_ptr<T>> container;

        uint containerSoftCapacity;
        uint containerNumObjects;
    }; // QuadTreeNode

    template <typename T>
    QuadTreeNode<T>::QuadTreeNode(const p2d::utility::Rect<float>& quadCoverage) 
    : coverage(quadCoverage),
      containerSoftCapacity(1),
      containerNumObjects(0),
      parentPtr(nullptr) {;}
} // namespace utility
} // namespace p2d

#endif