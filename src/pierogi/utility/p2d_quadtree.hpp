#ifndef P2D_QUADTREE_HPP
#define P2D_QUADTREE_HPP

#include "SDL.h"

#include "p2d_quadtreenode.hpp"
#include "p2d_rect.hpp"
#include "p2d_vector.hpp"
#include "../p2d_object.hpp"

#include <memory>

namespace p2d { namespace utility {
    typedef unsigned int uint;

    using p2d::math::Vector2f;

    template <uint N>
    class QuadTree {
    public:
        QuadTree(const Rect<float>& rectCoverage);

        void insert(std::shared_ptr<p2d::Object> objPtr);  
        void update();      

        inline QuadTreeNode<N>* getRoot() { return rootNode; }
        inline Rect<float> getCoverage() const { return rootNode->getCoverage(); }

        void draw(SDL_Renderer* renderer) const;
    private:
        QuadTreeNode<N>* rootNode = nullptr;
    }; // QuadTree

    template<uint N>
    QuadTree<N>::QuadTree(const Rect<float>& rectCoverage) {
        rootNode = new QuadTreeNode<N>(SubQuad::ROOT, rectCoverage);
    } // constructor

    template<uint N>
    void QuadTree<N>::insert(std::shared_ptr<p2d::Object> objPtr) {
        std::cout << "Insert object at " << objPtr.get() << " into quadtree." << std::endl;
        rootNode->insert(objPtr);
    } // insert

    template <uint N>
    void QuadTree<N>::draw(SDL_Renderer* renderer) const {
        rootNode->draw(renderer);
    }

} // namespace utility
} // namespace p2d

#endif