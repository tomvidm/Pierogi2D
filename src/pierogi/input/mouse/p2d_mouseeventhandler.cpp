#include "p2d_mouseeventhandler.hpp"

#include <iostream>

namespace p2d { namespace input {
    Event MouseEventHandler::onButtonPress(const SDL_MouseButtonEvent& sdlMouseButtonEvent) {
        debug::Logger::getInstancePtr()->log("onButtonPress");
        MouseEvent mouseEvent;

        switch (sdlMouseButtonEvent.button) {
            case SDL_BUTTON_LEFT:
                mouseStatePtr->setButtonPressState(MouseButton::LEFT, true);
                mouseEvent.button = MouseButton::LEFT;
                break;
            case SDL_BUTTON_MIDDLE:
                mouseStatePtr->setButtonPressState(MouseButton::MIDDLE, true);  
                mouseEvent.button = MouseButton::MIDDLE;
                break;
            case SDL_BUTTON_RIGHT:
                mouseStatePtr->setButtonPressState(MouseButton::RIGHT, true);
                mouseEvent.button = MouseButton::RIGHT;
                break;
            default:
                break;
        } // switch
        
        mouseEvent.position = Vector2i(sdlMouseButtonEvent.x,
                                       sdlMouseButtonEvent.y);
        std::cout << mouseEvent.position.getX() << std::endl;
        return Event(EventType::MOUSE_BUTTON_PRESS,
                     mouseEvent);
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
        mouseStatePtr->setMousePosition(Vector2i(sdlMouseMotionEvent.x,
                                                 sdlMouseMotionEvent.y));
        return Event(EventType::NONE);
    }
} // namespace input
} // namespace p2d