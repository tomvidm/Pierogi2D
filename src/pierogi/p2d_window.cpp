#include "p2d_window.hpp"

namespace p2d {
    // TODO: Break up into smaller functions
    // TODO: Fix error handling
    RenderWindow::RenderWindow() {
        ;
    } // RenderWindow

    RenderWindow::~RenderWindow() {
        SDL_DestroyWindow(sdlWindowPtr);
        SDL_DestroyRenderer(sdlRendererPtr);
        SDL_Quit();
    } // ~RenderWindow

    bool RenderWindow::initSDL() {
        std::cout << "SDL_Init" << std::endl;
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }
        return true;
    } // initSDL

    bool RenderWindow::initWindow() {
        std::cout << "SDL_CreateWindow" << std::endl;
        sdlWindowPtr = SDL_CreateWindow(
            "Default Window",
            500, 100,
            800, 600,
            SDL_WINDOW_SHOWN //| SDL_WINDOW_OPENGL
        ); // SDL_CreateWindow

        if (sdlWindowPtr == nullptr) {
            SDL_DestroyWindow(sdlWindowPtr);
            std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        } // if
        return true;
    } // initWindow

    bool RenderWindow::initRenderer() {
        std::cout << "SDL_CreateRenderer" << std::endl;
        sdlRendererPtr = SDL_CreateRenderer(
            sdlWindowPtr,
            -1, 0
        ); // SDL_CreateRenderer

        if (sdlRendererPtr == nullptr) {
            SDL_DestroyWindow(sdlWindowPtr);
            SDL_DestroyRenderer(sdlRendererPtr);
            std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        } // if
        return true;
    } // initWindow
} // namespace p2d