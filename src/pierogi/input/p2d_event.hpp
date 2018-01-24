#ifndef P2D_EVENT_HPP
#define P2D_EVENT_HPP

#include <queue>

#include "SDL.h"

#include "p2d_mouse.hpp"

namespace p2d { namespace input {
    enum EventType {
        NONE,
        QUIT,
        MOUSE_BUTTON_PRESS,
        MOUSE_BUTTON_RELEASE
    }; // EventType

    struct Event {
        Event(const EventType& eventType);
        EventType eventType;
        Uint32 timestamp;
        union {
            MouseEvent mouseEvent;
        };
    }; // Event

    class EventHandler {
    public:
        bool fetchEvent();
        Event getEvent() const;
    private:
        SDL_Event sdlEvent;
    }; // EventHandler
} // namespace input
} // namespace p2d

#endif