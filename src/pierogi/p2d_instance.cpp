#include "p2d_instance.hpp"

namespace p2d {
    Instance::Instance() {
        logger = p2d::debug::Logger::getInstancePtr();
        if (!init()) {
            std::cout << "Initialization failed!" << std::endl;
        } // if

       
    } // constructor

    Instance::~Instance() {
        delete logger;
    } // constructor

    void Instance::run() {
        p2d::utility::Rect<float> rect(64.f, 64.f, 640.f, 480.f);
        rootNodePtr = std::make_shared<QuadTreeNode<Object>>(rect);

        clk.reset();
        while (isRunning()) {
            handleInput();
            if (clk.getElapsedTime() > 33) {
                float dt = clk.getElapsedSeconds();
                clk.reset();
                update(dt);
                render();
            }
        } // while
    } // run

    void Instance::handleInput() {
        while (eventHandler.fetchEvent()) {
            event = eventHandler.getEvent();
            if (event.eventType == p2d::input::EventType::QUIT) {
                isRunning_ = false;
            } // if
            if (event.eventType == p2d::input::EventType::MOUSE_BUTTON_PRESS) {
                mousePos = event.mouseEvent.position.getFloatified();
                rootNodePtr->subdivByPosition(mousePos);
            }
        } // while
    } // handleInput

    void Instance::update(float dt) {
        for (auto objPtr : objects) {
            objPtr->move(math::Vector2f(10.f, 0.f) * dt);
        } // for
    } // move

    void Instance::render() {
        SDL_SetRenderDrawColor(renderWindow.getRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(renderWindow.getRenderer());
        SDL_SetRenderDrawColor(renderWindow.getRenderer(), 255, 255, 255, 255);
        rootNodePtr->draw(renderWindow.getRenderer());
        for (auto obj : objects) {
            SDL_RenderDrawPoint(renderWindow.getRenderer(),
                obj->getPosition().getIntified().getX(),
                obj->getPosition().getIntified().getY());
        }
        SDL_SetRenderDrawColor(renderWindow.getRenderer(), 255, 0, 0, 255);
        if (rootNodePtr->findSmallestQuadContaining(mousePos.getFloatified()) != nullptr) {
            rootNodePtr->findSmallestQuadContaining(mousePos.getFloatified())->draw(renderWindow.getRenderer());
        }
        SDL_RenderPresent(renderWindow.getRenderer());
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