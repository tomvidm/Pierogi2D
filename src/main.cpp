#include <iostream>

#include "SDL.h"
#include "p2d.hpp"

int main(int, char**)
{
    p2d::RenderWindow renderWindow;

    p2d::Clock clk;
    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } // if
        } // while
        if (clk.getElapsedTime() > 500)
        {
            clk.reset();
            renderWindow.blink();
            std::cout << "I'm here!" << std::endl;
        }
    } // while

    return 0;
} // int main