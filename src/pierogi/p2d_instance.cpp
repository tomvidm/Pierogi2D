#include "p2d_instance.hpp"

namespace p2d {
    Instance::Instance() {
        init();
    } // constructor

    void Instance::run() {
        p2d::Clock clk;
    } // run

    void Instance::init() {
        renderWindow.initSDL();
        renderWindow.initWindow();
        renderWindow.initGLContext();
        renderWindow.initGL();
    } // init
}