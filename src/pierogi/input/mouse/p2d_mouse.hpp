#ifndef P2D_MOUSE_HPP
#define P2D_MOUSE_HPP

#include "p2d_math.hpp"

namespace p2d { namespace input {
    using p2d::math::Vector2i;
    using p2d::math::Vector2f;

    enum MouseButton {
        LEFT = 0,
        MIDDLE = 1,
        RIGHT = 2,
        NUM_MOUSE_BUTTONS = 3
    }; // MouseButton

    enum MouseEventType {
        PRESSED,
        RELEASED,
        MOTION
    }; // MouseEventType

    // This struct holds information about the mouse event
    struct MouseEvent {
        MouseButton button;
        Vector2i position;
        Vector2i diff;
    }; // MouseEvent
} // namespace input
} // namespace p2d

#endif