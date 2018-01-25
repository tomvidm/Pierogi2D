#ifndef P2D_WINDOW_HPP
#define P2D_WINDOW_HPP

#include <iostream>

#include "GL/glew.h"
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
        bool initGLContext();
        bool initGL();

        void renderDummy();
    private:
        SDL_Window* sdlWindowPtr;
        SDL_Renderer* sdlRendererPtr;
        SDL_GLContext glContext;
    }; // class RenderWindow
} // namespace p2d

#endif