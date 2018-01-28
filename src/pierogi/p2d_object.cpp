#include "p2d_object.hpp"

namespace p2d {
    void Object::setPosition(const math::Vector2f& pos) {
        position = pos;
    } // setPosition

    math::Vector2f Object::getPosition() const {
        return position;
    } // getPosition
} // namespace p2d