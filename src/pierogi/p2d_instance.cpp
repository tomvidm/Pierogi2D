#include "p2d_instance.hpp"

namespace p2d {
    Instance::Instance() {
        logger = p2d::debug::Logger::getInstancePtr();
        if (!init()) {
            std::cout << "Initialization failed!" << std::endl;
        } // if

        run();
    } // constructor

    Instance::~Instance() {
        delete logger;
    } // constructor

    void Instance::run() {
        p2d::Clock clk;
        p2d::input::Event event;
        while (isRunning()) {
            while (eventHandler.fetchEvent()) {
                if (event.eventType == p2d::input::EventType::QUIT) {
                    isRunning_ = false;
                } // if
            } // while

            if (clk.getElapsedTime() > framePeriod_) {
                clk.reset();
            } // if
        }
    } // run

    bool Instance::init() {
        // If any of them fails, initialization fails.
        if (renderWindow.initSDL() ||
            renderWindow.initWindow() ||
            renderWindow.initRenderer()) {
            return true;
        } else {
            return false;
        } // if else
    } // init
}