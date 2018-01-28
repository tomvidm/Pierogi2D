#include "p2d_instance.hpp"

namespace p2d {
    Instance::Instance() {
        logger = p2d::debug::Logger::getInstancePtr();
        if (!init()) {
            std::cout << "Initialization failed!" << std::endl;
        } // if

        using p2d::math::Vector2f;
        qtree.setRectCoverage(rect);
    } // constructor

    Instance::~Instance() {
        delete logger;
    } // constructor

    void Instance::run() {
        while (isRunning()) {
            handleInput();
            render();
        } // while
    } // run

    void Instance::handleInput() {
        while (eventHandler.fetchEvent()) {
            event = eventHandler.getEvent();
            if (event.eventType == p2d::input::EventType::QUIT) {
                isRunning_ = false;
            } // if
            if (event.eventType == p2d::input::EventType::MOUSE_BUTTON_PRESS) {
                Object obj;
                obj.setPosition(event.mouseEvent.position.getFloatified());
                objects.push_back(obj);
                qtree.insert(&(objects[objects.size() - 1]));
                }
        } // while
    } // handleInput

    void Instance::render() {
        if (clk.getElapsedTime() > framePeriod_) {
            clk.reset();
            SDL_SetRenderDrawColor(renderWindow.getRenderer(), 92, 92, 92, 255);
            SDL_RenderClear(renderWindow.getRenderer());
            qtree.draw(renderWindow.getRenderer());
            for (auto obj : objects) {
                int x = obj.getPosition().getIntified().getX();
                int y = obj.getPosition().getIntified().getY();
                SDL_RenderDrawPoint(renderWindow.getRenderer(), x, y);
            }
            SDL_RenderPresent(renderWindow.getRenderer());
        } // if
    } // render

    bool Instance::init() {
        // If any of them fails, initialization fails.
        if (renderWindow.initSDL() &&
            renderWindow.initWindow() &&
            renderWindow.initRenderer()) {
            return true;
        } else {
            return false;
        } // if else
    } // init
}