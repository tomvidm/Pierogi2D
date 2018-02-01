#include "p2d_viewport.hpp"

namespace p2d {
    math::Vector2f Viewport::toScreenSpace(const math::Vector2f& vec) {
        return vec;
    } // toScreenSpace

    math::Vector2f Viewport::toScreenSpace(const math::Vector2f& vec) {
        return viewportRect.getOrigin() + vec;
    } // toWorldSpace
} // namespace p2d