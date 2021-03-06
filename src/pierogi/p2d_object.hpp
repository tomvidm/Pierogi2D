#ifndef P2D_OBJECT_HPP
#define P2D_OBJECT_HPP

#include "p2d_vector.hpp"
#include "p2d_compiletimeconstants.hpp"
#include "p2d_clock.hpp"


namespace p2d {
    class Object {
    public:
        Object();
        Object(const Object& other);
        void setPosition(const math::Vector2f& pos);
        void setPosition(const float& x, const float& y);

        void move(const math::Vector2f& pos);
        math::Vector2f getPosition() const;

        bool isInsideQuad() const;
    private:
        math::Vector2f position;
    }; // Object
} // namespace p2d

#endif