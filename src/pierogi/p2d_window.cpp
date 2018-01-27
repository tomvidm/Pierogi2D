#include "p2d_window.hpp"

namespace p2d {
    // TODO: Break up into smaller functions
    // TODO: Fix error handling
    RenderWindow::RenderWindow() {
        initSDL();
        initWindow();
    } // RenderWindow

    RenderWindow::~RenderWindow() {
        SDL_DestroyWindow(sdlWindowPtr);
        SDL_Quit();
    } // ~RenderWindow

    bool RenderWindow::initSDL() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }
        return true;
    } // initSDL

    bool RenderWindow::initWindow() {
        sdlWindowPtr = SDL_CreateWindow(
            "Default Window",
            900, 100,
            640, 480,
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
        sdlRendererPtr = SDL_CreateRenderer(
            sdlWindowPtr,
            -1,
            SDL_RENDERER_ACCELERATED ||
            SDL_RENDERER_PRESENTVSYNC
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