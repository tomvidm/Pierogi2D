#include <iostream>

#include "SDL.h"
#include "p2d.hpp"

int main(int, char**)
{
    p2d::RenderWindow renderWindow;

    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        renderWindow.blink();
    }

    return 0;
}