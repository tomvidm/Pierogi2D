#include "p2d_mouseeventhandler.hpp"

#include <iostream>

namespace p2d { namespace input {
    Event MouseEventHandler::onButtonPress(const SDL_Event& sdlEvent) {
        std::cout << "onButtonPress" << std::endl;
        switch (sdlEvent.button.button) {
            case SDL_BUTTON_LEFT:
                return Event(EventType::NONE);
            case SDL_BUTTON_MIDDLE:
                return Event(EventType::NONE);
            case SDL_BUTTON_RIGHT:
                return Event(EventType::NONE);
            default:
                return Event(EventType::NONE);
        } // switch
    } // onButtonPress

    Event MouseEventHandler::onButtonRelease(const SDL_Event& sdlEvent) {
        std::cout << "onButtonRelease" << std::endl;
        switch (sdlEvent.button.button) {
            case SDL_BUTTON_LEFT:
                return Event(EventType::NONE);
            case SDL_BUTTON_MIDDLE:
                return Event(EventType::NONE);
            case SDL_BUTTON_RIGHT:
                return Event(EventType::NONE);
            default:
                return Event(EventType::NONE);
        } // switch
    } // onButtonPress
} // namespace input
} // namespace p2d