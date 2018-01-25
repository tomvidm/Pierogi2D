#include "p2d_event.hpp"

namespace p2d { namespace input {
    Event::Event(const EventType& eventType)
    : eventType(eventType), timestamp(SDL_GetTicks()) {
        ;
    } // constructor
} // namespace input
} // namespace p2d