#ifndef P2D_MOUSEEVENTHANDLER_HPP
#define P2D_MOUSEEVENTHANDLER_HPP

#include "SDL.h"

#include "p2d_debug.hpp"
#include "p2d_event.hpp"
#include "p2d_mouse.hpp"
#include "p2d_mousestate.hpp"

namespace p2d { namespace input {
    class MouseEventHandler {
    public:
        Event onButtonPress(const SDL_Event& sdlEvent);
        Event onButtonRelease(const SDL_Event& sdlEvent);
    private:
        MouseState* mouesStatePtr = MouseState::getInstancePtr();
    }; // MouseEventHandler
} // namespace input
} // namespace p2d

#endif