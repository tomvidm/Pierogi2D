#ifndef P2D_VIEWPORT_HPP
#define P2D_VIEWPORT_HPP

#include "p2d_math.hpp"
#include "p2d_utility.hpp"

namespace p2d {
    class Viewport {
    public:
        math::Vector2f toScreenSpace(const math::Vector2f& vec) const;
        math::Vector2f toWorldSpace(const math::Vector2f& vec) const;

        void moveTo(const math::Vector2f& pos);
        void moveRelative(const math::Vector2f& dpos);
    private:
        utility::Rect<float> viewportRect;
    }; // Viewport
} // namespace p2d

#endif