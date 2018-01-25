#ifndef P2D_EVENTHANDLER_HPP
#define P2D_EVENTHANDLER_HPP

#include <queue>

#include "SDL.h"

#include "p2d_event.hpp"
#include "mouse/p2d_mouse.hpp"
#include "mouse/p2d_mouseeventhandler.hpp"

namespace p2d { namespace input {
    class EventHandler {
    public:
        bool fetchEvent();
        Event getEvent();
    private:
        MouseEventHandler mouseEventHandler;

        SDL_Event sdlEvent;
    }; // EventHandler
} // namespace input
} // namespace p2d

#endif