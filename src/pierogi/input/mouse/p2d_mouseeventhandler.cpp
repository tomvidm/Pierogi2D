#include "p2d_mouseeventhandler.hpp"

#include <iostream>

namespace p2d { namespace input {
    Event MouseEventHandler::onButtonPress(const SDL_MouseButtonEvent& sdlMouseButtonEvent) {
        debug::Logger::getInstancePtr()->log("onButtonPress");
        switch (sdlMouseButtonEvent.button) {
            case SDL_BUTTON_LEFT:
                mouseStatePtr->setButtonPressState(MouseButton::LEFT, true);
                break;
            case SDL_BUTTON_MIDDLE:
                mouseStatePtr->setButtonPressState(MouseButton::MIDDLE, true);  
                break;
            case SDL_BUTTON_RIGHT:
                mouseStatePtr->setButtonPressState(MouseButton::RIGHT, true);
                break;
            default:
                break;
        } // switch

        mouseStatePtr->setMousePosition(Vector2i(sdlMouseButtonEvent.x,
                                                 sdlMouseButtonEvent.y));
        return Event(EventType::NONE);
    } // onButtonPress

    Event MouseEventHandler::onButtonRelease(const SDL_MouseButtonEvent& sdlMouseButtonEvent) {
        debug::Logger::getInstancePtr()->log("onButtonRelease");
        switch (sdlMouseButtonEvent.button) {
            case SDL_BUTTON_LEFT:
                mouseStatePtr->setButtonPressState(MouseButton::LEFT, false);
                return Event(EventType::NONE);
            case SDL_BUTTON_MIDDLE:
                mouseStatePtr->setButtonPressState(MouseButton::MIDDLE, false);
                return Event(EventType::NONE);
            case SDL_BUTTON_RIGHT:
                mouseStatePtr->setButtonPressState(MouseButton::RIGHT, false);
                return Event(EventType::NONE);
            default:
                return Event(EventType::NONE);
        } // switch
    } // onButtonPress

    Event MouseEventHandler::onMotion(const SDL_MouseMotionEvent& sdlMouseMotionEvent) {
        debug::Logger::getInstancePtr()->log("onMotion");
        mouseStatePtr->setMousePosition(Vector2i(sdlMouseMotionEvent.x,
                                                 sdlMouseMotionEvent.y));
        return Event(EventType::NONE);
    }
} // namespace input
} // namespace p2d