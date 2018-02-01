#ifndef P2D_GLWINDOW_HPP
#define P2D_GLWINDOW_HPP

#include <iostream>

#include "GL/glew.h"

#include "SDL.h"
#include "SDL_opengl.h"

#include "p2d_viewport.hpp"
#include "p2d_typedefs.hpp"

/*
    p2d_window defines the classes and functions related to the maintenance and creation/destruction of windows.
*/

namespace p2d {
    class GLWindow {
    public:
        GLWindow();
        ~GLWindow();

        bool initSDL();
        bool initWindow();
        bool initOpenGL();

        void flip() const;
        void render();

        inline Viewport& getViewport() { return viewport; }

        inline SDL_Window* getWindow() { return sdlWindowPtr; }
    private:
        SDL_Window* sdlWindowPtr;

        Viewport viewport;
    }; // class GLWindow
} // namespace p2d

#endif