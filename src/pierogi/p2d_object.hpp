#ifndef P2D_OBJECT_HPP
#define P2D_OBJECT_HPP

#include "p2d_vector.hpp"
#include "p2d_compiletimeconstants.hpp"

namespace p2d {
    typedef unsigned int uint;
    template <uint N>
    class QuadTreeNode;

    class Object {
    public:
        Object();
        Object(const Object& other);
        void setPosition(const math::Vector2f& pos);
        void setPosition(const float& x, const float& y);
        // SET QUAD
        void move(const math::Vector2f& pos);
        math::Vector2f getPosition() const;
    private:
        math::Vector2f position;
        QuadTreeNode<QUADTREE_NODE_OBJECT_CAPACITY>* quadPtr;
    }; // Object
} // namespace p2d

#endif