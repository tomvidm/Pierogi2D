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
        p2d::utility::Rect<float> qtreeCoverage(16.f, 16.f, 600, 400);
        qtreePtr = new p2d::utility::QuadTree<QUADTREE_NODE_OBJECT_CAPACITY> (qtreeCoverage);
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
                math::Vector2f pos = event.mouseEvent.position.getFloatified();
                if (!qtreePtr->getCoverage().contains(pos)) {
                    continue;
                } // if
                objects.push_back(std::make_shared<Object>());
                objects[objects.size() - 1]->setPosition(pos);
                qtreePtr->insert(*objects[objects.size() - 1]);
            }
        } // while
    } // handleInput

    void Instance::update(float dt) {
        for (auto objPtr : objects) {
            ;//objPtr->move(math::Vector2f(10.f, 0.f) * dt);
        } // for
    } // move

    void Instance::render() {
        SDL_SetRenderDrawColor(renderWindow.getRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(renderWindow.getRenderer());
        qtreePtr->draw(renderWindow.getRenderer());
        SDL_SetRenderDrawColor(renderWindow.getRenderer(), 255, 0, 0, 255);
        for (auto obj : objects) {
            SDL_RenderDrawPoint(renderWindow.getRenderer(),
                obj->getPosition().getIntified().getX(),
                obj->getPosition().getIntified().getY());
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