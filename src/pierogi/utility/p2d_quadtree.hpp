#ifndef P2D_QUADTREE_HPP
#define P2D_QUADTREE_HPP

#include "SDL.h"

#include "p2d_quadtreenode.hpp"
#include "p2d_rect.hpp"
#include "p2d_vector.hpp"
#include "../p2d_object.hpp"

namespace p2d { namespace utility {
    typedef unsigned int uint;

    using p2d::math::Vector2f;

    template <uint N>
    class QuadTree {
    public:
        QuadTree(const Rect<float>& rectCoverage);

        void insert(p2d::Object& obj);        

        inline QuadTreeNode<N>* getRoot() { return rootNode; }

        void draw(SDL_Renderer* renderer) const;
    private:
        QuadTreeNode<N>* rootNode = nullptr;
    }; // QuadTree

    template<uint N>
    QuadTree<N>::QuadTree(const Rect<float>& rectCoverage) {
        rootNode = new QuadTreeNode<N>(SubQuad::ROOT, rectCoverage);
    } // constructor

    template<uint N>
    void QuadTree<N>::insert(p2d::Object& obj) {
        std::cout << "Insert object at " << &obj << " into quadtree." << std::endl;
        rootNode->insert(obj);
    } // insert

    template <uint N>
    void QuadTree<N>::draw(SDL_Renderer* renderer) const {
        rootNode->draw(renderer);
    }

} // namespace utility
} // namespace p2d

#endif