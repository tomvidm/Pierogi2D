#ifndef P2D_QUADTREE_HPP
#define P2D_QUADTREE_HPP

#include "SDL.h"

#include "p2d_quadtreenode.hpp"
#include "p2d_rect.hpp"
#include "p2d_vector.hpp"
#include "../p2d_object.hpp"

#include <memory>
#include <iostream>

namespace p2d { namespace utility {
    typedef unsigned int uint;

    using p2d::math::Vector2f;

    template <typename T>
    class QuadTree {
    public:
        QuadTree();
        QuadTree(const p2d::utility::Rect<float>& quadCoverage);
        void setCoverage(const p2d::utility::Rect<float>& quadCoverage);
        void setCapacity(const uint cap);
        void insert(const std::shared_ptr<p2d::Object>& objPtr);
        void draw(SDL_Renderer* renderer) const;

        inline uint getNumContainedObjects() const { return rootNodePtr->getNumContainedObjects(); }

        std::shared_ptr<QuadTreeNode<T>> getQuadByPosition(const p2d::math::Vector2f& pos) const;
    private:
        std::shared_ptr<QuadTreeNode<T>> rootNodePtr;
    }; // QuadTree

    template <typename T>
    QuadTree<T>::QuadTree() {
        ;
    }

    template <typename T>
    QuadTree<T>::QuadTree(const p2d::utility::Rect<float>& quadCoverage) {
        rootNodePtr = std::make_shared<QuadTreeNode<T>>(quadCoverage);
    }

    template <typename T>
    void QuadTree<T>::setCoverage(const p2d::utility::Rect<float>& quadCoverage) {
        rootNodePtr->setQuadRectCoverage(quadCoverage);
    }

    template <typename T>
    void QuadTree<T>::setCapacity(const uint cap) {
        rootNodePtr->setContainerCapacity(cap);
    }

    template <typename T>
    void QuadTree<T>::insert(const std::shared_ptr<p2d::Object>& objPtr) {
        std::cout << "Inserting object at posiion " << objPtr->getPosition().getX() << ", " << objPtr->getPosition().getY() << std::endl;
        rootNodePtr->insert(objPtr);
    }

    template <typename T>
    void QuadTree<T>::draw(SDL_Renderer* renderer) const {
        rootNodePtr->draw(renderer);
    }

    template <typename T>
    std::shared_ptr<QuadTreeNode<T>> QuadTree<T>::getQuadByPosition(const p2d::math::Vector2f& pos) const {
        return rootNodePtr->findSmallestQuadContaining(pos);
    }

} // namespace utility
} // namespace p2d

#endif