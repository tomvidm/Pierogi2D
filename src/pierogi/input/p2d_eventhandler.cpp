#include "p2d_eventhandler.hpp"

namespace p2d { namespace input {
    bool EventHandler::fetchEvent() {
        if (SDL_PollEvent(&sdlEvent)) {
            return true;
        } else {
            return false;
        }
    } // fetchEvent

    Event EventHandler::getEvent() {
        switch (sdlEvent.type) {
            case SDL_QUIT:
                return Event(EventType::QUIT);
            case SDL_MOUSEBUTTONDOWN:
                return mouseEventHandler.onButtonPress(sdlEvent);
            case SDL_MOUSEBUTTONUP:
                return mouseEventHandler.onButtonRelease(sdlEvent);
            default:
                return Event(EventType::NONE);
        } // switch
    } // getEvent
} // namespace input
} // namespace p2d