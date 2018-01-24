#include <iostream>

#include "SDL.h"
#include "p2d.hpp"

int main(int, char**)
{
    p2d::RenderWindow renderWindow;
    p2d::math::Vector<float, 3> vec1;
    p2d::math::Vector<float, 3> vec2;
    vec1[1] = 1;
    vec1 += vec2;
    p2d::Clock clk;
    p2d::input::EventHandler eventHandler;
    bool quit = false;
    while (!quit) {
        while (eventHandler.fetchEvent()) {
            p2d::input::Event e = eventHandler.getEvent();
            if (e.eventType == p2d::input::EventType::QUIT) {
                quit = true;
            } // if
        } // while
        if (clk.getElapsedTime() > 500)
        {
            std::cout << clk.getElapsedSeconds() << std::endl;
            clk.reset();
            renderWindow.blink();
            vec1 *= 2;
        }
    } // while

    return 0;
} // int main