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

    Event::Event(const EventType& eventType, const MouseEvent& mouseEvent) 
    : eventType(eventType),
      mouseEvent(mouseEvent),
      timestamp(SDL_GetTicks()) {
        ;
    } // copy constructor

    Event::Event(const Event& other) 
    : eventType(other.eventType),
      timestamp(other.timestamp) {
        switch(eventType) {
            case EventType::MOUSE_BUTTON_PRESS:
            case EventType::MOUSE_BUTTON_RELEASE:
            case EventType::MOUSE_MOTION:
                mouseEvent = other.mouseEvent;
            case EventType::QUIT:
                break;
            default:
                break;
        } // switch
    } // copy constructor

} // namespace input
} // namespace p2d