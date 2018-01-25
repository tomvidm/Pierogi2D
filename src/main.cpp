#include <iostream>

#include "GL/glew.h"
#include "SDL.h"
#include "p2d.hpp"

int main(int, char**)
{
    p2d::RenderWindow renderWindow;

    p2d::Clock clk1;
    p2d::Clock clk2;
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
        if (clk1.getElapsedTime() > 200)
        {
            std::cout << "clk1: " << clk1.getElapsedSeconds() << std::endl;
            clk1.reset();
            renderWindow.renderDummy();
        }

        if (clk2.getElapsedTime() > 400)
        {
            std::cout << "clk2: " << clk2.getElapsedSeconds() << std::endl;
            clk2.reset();
        }

    } // while

    return 0;
} // int main