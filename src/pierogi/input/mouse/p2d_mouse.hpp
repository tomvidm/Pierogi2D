#ifndef P2D_MOUSE_HPP
#define P2D_MOUSE_HPP

namespace p2d { namespace input {
    enum MouseButton {
        LEFT = 0,
        MIDDLE = 1,
        RIGHT = 2,
        NUM_MOUSE_BUTTONS = 3
    }; // MouseButton

    enum MouseEventType {
        PRESSED,
        RELEASED
    }; // MouseEventType

    // This struct holds information about the mouse event
    struct MouseEvent {
        MouseButton button;
    }; // MouseEvent
} // namespace input
} // namespace p2d

#endif