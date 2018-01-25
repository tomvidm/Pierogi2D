#include "p2d_mouseeventhandler.hpp"

#include <iostream>

namespace p2d { namespace input {
    Event MouseEventHandler::onButtonPress(const SDL_Event& sdlEvent) {
        debug::Logger::getInstancePtr()->log("onButtonPress");
        switch (sdlEvent.button.button) {
            case SDL_BUTTON_LEFT:
                mouesStatePtr->setButtonPressState(MouseButton::LEFT, true);
                return Event(EventType::NONE);
            case SDL_BUTTON_MIDDLE:
                mouesStatePtr->setButtonPressState(MouseButton::MIDDLE, true);  
                return Event(EventType::NONE);
            case SDL_BUTTON_RIGHT:
                mouesStatePtr->setButtonPressState(MouseButton::RIGHT, true);
                return Event(EventType::NONE);
            default:
                return Event(EventType::NONE);
        } // switch
    } // onButtonPress

    Event MouseEventHandler::onButtonRelease(const SDL_Event& sdlEvent) {
        debug::Logger::getInstancePtr()->log("onButtonRelease");
        switch (sdlEvent.button.button) {
            case SDL_BUTTON_LEFT:
                mouesStatePtr->setButtonPressState(MouseButton::LEFT, false);
                return Event(EventType::NONE);
            case SDL_BUTTON_MIDDLE:
                mouesStatePtr->setButtonPressState(MouseButton::MIDDLE, false);
                return Event(EventType::NONE);
            case SDL_BUTTON_RIGHT:
                mouesStatePtr->setButtonPressState(MouseButton::RIGHT, false);
                return Event(EventType::NONE);
            default:
                return Event(EventType::NONE);
        } // switch
    } // onButtonPress
} // namespace input
} // namespace p2d