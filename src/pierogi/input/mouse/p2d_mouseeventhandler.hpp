#ifndef P2D_MOUSEEVENTHANDLER_HPP
#define P2D_MOUSEEVENTHANDLER_HPP

#include "SDL.h"

#include "p2d_debug.hpp"

#include "../p2d_event.hpp"

#include "p2d_mouse.hpp"
#include "p2d_mousestate.hpp"

namespace p2d { namespace input {
    class MouseEventHandler {
    public:
        Event onButtonPress(const SDL_MouseButtonEvent& sdlMouseButtonEvent);
        Event onButtonRelease(const SDL_MouseButtonEvent& sdlMouseButtonEvent);
        Event onMotion(const SDL_MouseMotionEvent& sdlMouseMotionEvent);
    private:
        MouseState* mouseStatePtr = MouseState::getInstancePtr();
    }; // MouseEventHandler
} // namespace input
} // namespace p2d

#endif