#ifndef P2D_OBJECT_HPP
#define P2D_OBJECT_HPP

#include "p2d_vector.hpp"

namespace p2d {
    class Object {
    public:
        void setPosition(const math::Vector2f& pos);
        math::Vector2f getPosition() const;
    private:
        math::Vector2f position;
    }; // Object
} // namespace p2d

#endif