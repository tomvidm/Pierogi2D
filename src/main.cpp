#include <iostream>

#include "SDL.h"
#include "p2d.hpp"

int main(int, char**)
{
    p2d::RenderWindow renderWindow;
    p2d::Clock clk;
    p2d::input::EventHandler eventHandler;
    p2d::math::Vector2f a(1.f, 2.f);
    p2d::math::Vector3f b(1.f, 2.f, 3.f);
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
        }
    } // while

    return 0;
} // int main