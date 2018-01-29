#include "p2d_object.hpp"

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

    void Object::move(const math::Vector2f& vel) {
        position += vel;
    }

    math::Vector2f Object::getPosition() const {
        return position;
    } // getPosition
} // namespace p2d