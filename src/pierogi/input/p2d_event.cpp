#include "p2d_event.hpp"

namespace p2d { namespace input {
    Event::Event()
    : eventType(EventType::NONE), timestamp(SDL_GetTicks()) {
        ;
    } // constructor

    Event::Event(const EventType& eventType)
    : eventType(eventType), timestamp(SDL_GetTicks()) {
        ;
    } // constructor

    Event::Event(const Event& other) 
    : eventType(other.eventType),
      timestamp(other.timestamp) {
        switch(eventType) {
            case EventType::MOUSE_BUTTON_PRESS:
            case EventType::MOUSE_BUTTON_RELEASE:
                mouseEvent = other.mouseEvent;
            case EventType::QUIT:
                break;
            default:
                break;
        } // switch
    }
} // namespace input
} // namespace p2d