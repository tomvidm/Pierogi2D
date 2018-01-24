#include "p2d_window.hpp"

namespace p2d {
    // TODO: Break up into smaller functions
    // TODO: Fix error handling
    RenderWindow::RenderWindow() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0){
            std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return;
        }

        // Create sdl window
        sdlWindowPtr = SDL_CreateWindow(
                            "Default Window",
                            900, 100,
                            640, 480,
                            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
                            );

        if (sdlWindowPtr == nullptr) {
            SDL_DestroyWindow(sdlWindowPtr);
            std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return;
        }

        glContext = SDL_GL_CreateContext(sdlWindowPtr);
        glewInit();
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    } // RenderWindow

    RenderWindow::~RenderWindow() {
        SDL_DestroyWindow(sdlWindowPtr);
        SDL_Quit();
    } // ~RenderWindow
} // namespace p2d