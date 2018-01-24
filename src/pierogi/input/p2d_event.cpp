#include "p2d_event.hpp"

namespace p2d { namespace input {
    Event::Event(const EventType& eventType)
    : eventType(eventType), timestamp(SDL_GetTicks()) {
        ;
    } // constructor

    bool EventHandler::fetchEvent() {
        if (SDL_PollEvent(&sdlEvent)) {
            return true;
        } else {
            return false;
        }
    } // fetchEvent

    Event EventHandler::getEvent() const {
        switch (sdlEvent.type) {
            case SDL_QUIT:
                return Event(EventType::QUIT);
            default:
                return Event(EventType::NONE);
        } // switch
    } // getEvent
} // namespace input
} // namespace p2d