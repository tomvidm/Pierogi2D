#include "p2d_object.hpp"
#include "p2d_quadtreenode.hpp"

namespace p2d {
    Object::Object() {
        ;
    }

    Object::Object(const Object& other) {
        position = other.getPosition();
    }

    void Object::setPosition(const math::Vector2f& pos) {
        position = pos;
    } // setPosition

    void Object::setPosition(const float& x, const float& y) {
        position = math::Vector2f(x, y);
    } // setPosition

    void Object::setQuad(utility::QuadTreeNode<QUADTREE_NODE_OBJECT_CAPACITY>* quad) {
        quadPtr = quad;
    } // setQuad

    utility::QuadTreeNode<QUADTREE_NODE_OBJECT_CAPACITY>* Object::getQuadPtr() {
        return quadPtr;
    }

    void Object::move(const math::Vector2f& vel) {
        position += vel;
    } // move

    math::Vector2f Object::getPosition() const {
        return position;
    } // getPosition

    bool Object::isInsideQuad() const {
        if (quadPtr->coversPoint(position)) {
            return true;
        } else {
            return false;
        } // if else
    } // isInsideQuad

    void Object::update() {
        if (!isInsideQuad()) {
            quadPtr->remove(this);
        }
    }
} // namespace p2d