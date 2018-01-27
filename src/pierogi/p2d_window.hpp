#ifndef P2D_WINDOW_HPP
#define P2D_WINDOW_HPP

#include <iostream>

#include "SDL.h"
#include "p2d_typedefs.hpp"

/*
    p2d_window defines the classes and functions related to the maintenance and creation/destruction of windows.
*/

namespace p2d {
    class RenderWindow {
    public:
        RenderWindow();
        ~RenderWindow();

        bool initSDL();
        bool initWindow();
        bool initRenderer();

        inline SDL_Window* getWindow() { return sdlWindowPtr; }
        inline SDL_Renderer* getRenderer() { return sdlRendererPtr; }
    private:
        SDL_Window* sdlWindowPtr;
        SDL_Renderer* sdlRendererPtr;
    }; // class RenderWindow
} // namespace p2d

#endif