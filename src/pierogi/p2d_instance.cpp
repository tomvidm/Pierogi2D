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
        quadTreePtr = std::make_shared<p2d::utility::QuadTree<Object>>(rect);

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
                break;
            } // if
            if (event.eventType == p2d::input::EventType::MOUSE_MOTION) {
                mousePos = event.mouseEvent.position.getFloatified();
                break;
            }
            if (event.eventType == p2d::input::EventType::MOUSE_BUTTON_PRESS) {
                switch (event.mouseEvent.button) {
                    case p2d::input::MouseButton::LEFT:
                    case p2d::input::MouseButton::RIGHT:
                    default:
                        break;
                } // switch
            } // if
        } // while
    } // handleInput

    void Instance::update(float dt) {
        for (auto objPtr : objectPtrs) {
            ;//objPtr->move(math::Vector2f(10.f, 0.f) * dt);
        } // for
    } // move

    void Instance::render() {
        SDL_SetRenderDrawColor(renderWindow.getRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(renderWindow.getRenderer());
        SDL_SetRenderDrawColor(renderWindow.getRenderer(), 92, 92, 92, 255);
        quadTreePtr->draw(renderWindow.getRenderer());
        for (auto objPtr : objectPtrs) {
            SDL_RenderDrawPoint(renderWindow.getRenderer(),
                objPtr->getPosition().getIntified().getX(),
                objPtr->getPosition().getIntified().getY());
        }
        SDL_SetRenderDrawColor(renderWindow.getRenderer(), 255, 0, 0, 255);
        if (quadTreePtr->getQuadByPosition(mousePos.getFloatified()) != nullptr) {
            quadTreePtr->getQuadByPosition(mousePos.getFloatified())->draw(renderWindow.getRenderer());
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