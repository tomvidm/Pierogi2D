#ifndef P2D_MOUSE_HPP
#define P2D_MOUSE_HPP

namespace p2d { namespace input {
    enum MouseButton {
        LEFT,
        MIDDLE,
        RIGHT
    }; // MouseButton

    struct MouseEvent {
        MouseButton button;
    }; // MouseEvent
} // namespace input
} // namespace p2d

#endif