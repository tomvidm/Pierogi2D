#ifndef P2D_EVENT_HPP
#define P2D_EVENT_HPP

#include <queue>

#include "SDL.h"

#include "mouse/p2d_mouse.hpp"

namespace p2d { namespace input {
    enum EventType {
        NONE,
        QUIT,
        MOUSE_BUTTON_PRESS,
        MOUSE_BUTTON_RELEASE,
        MOUSE_MOTION
    }; // EventType

    // The Event struct holds information about the event,
    // the time and a union holding the different Event types.
    struct Event {
        Event();
        Event(const EventType& eventType);
        Event(const EventType& eventType, const MouseEvent& mouseEvent);
        Event(const Event& other);
        EventType eventType;
        Uint32 timestamp;
        union {
            MouseEvent mouseEvent;
        }; // union
    }; // Event
} // namespace input
} // namespace p2d

#endif