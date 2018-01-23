#include "p2d_window.hpp"

namespace p2d {
    // This function simply clears the framebuffer and flips it again.
    void RenderWindow::blink() {
        SDL_RenderClear(sdlRendererPtr);
        SDL_RenderPresent(sdlRendererPtr);
    } // void blink()

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
                            100, 100,
                            640, 480,
                            SDL_WINDOW_SHOWN
                            );

        if (sdlWindowPtr == nullptr) {
            SDL_DestroyWindow(sdlWindowPtr);
            std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return;
        }

        // Create sdl renderer and associate with sdl window
        sdlRendererPtr = SDL_CreateRenderer(
                            sdlWindowPtr,
                            -1,
                            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
                            );

        if (sdlRendererPtr == nullptr) {
            SDL_DestroyRenderer(sdlRendererPtr);
            SDL_DestroyWindow(sdlWindowPtr);
            std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return;
        }
    } // RenderWindow

    RenderWindow::~RenderWindow() {
        SDL_DestroyWindow(sdlWindowPtr);
        SDL_DestroyWindow(sdlWindowPtr);
        SDL_Quit();
    } // ~RenderWindow
} // namespace p2d