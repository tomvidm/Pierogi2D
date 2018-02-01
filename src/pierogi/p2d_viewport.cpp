#include "p2d_viewport.hpp"

namespace p2d {
    math::Vector2f Viewport::toScreenSpace(const math::Vector2f& vec) const {
        return vec;
    } // toScreenSpace

    math::Vector2f Viewport::toWorldSpace(const math::Vector2f& vec) const {
        return viewportRect.getOrigin() + vec;
    } // toWorldSpace

    void Viewport::moveTo(const math::Vector2f& pos) {
        viewportRect.setOrigin(pos);
    } // moveTo

    void Viewport::moveRelative(const math::Vector2f& pos) {
        viewportRect += pos;
    } // moveTo
} // namespace p2d