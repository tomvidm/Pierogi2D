#ifndef P2D_INSTANCE_HPP
#define P2D_INSTANCE_HPP

#include "p2d_logger.hpp"
#include "p2d_clock.hpp"
#include "p2d_eventhandler.hpp"
#include "p2d_logger.hpp"
#include "p2d_typedefs.hpp"
#include "p2d_utility.hpp"
#include "p2d_object.hpp"
#include "p2d_window.hpp"

namespace p2d {
    class Instance {
    public:
        Instance();
        ~Instance();

        void run();

        inline bool isRunning() const { return isRunning_; }
    private:
        bool init();
        void handleInput();
        void render();
        p2d::RenderWindow renderWindow;
        p2d::input::EventHandler eventHandler;
        p2d::debug::Logger* logger;

        p2d::input::Event event;
        p2d::Clock clk;

        p2d::utility::Rect<float> rect = p2d::utility::Rect<float>(10.f, 10.f, 600.f, 400.f);
        p2d::utility::QuadTreeNode<Object, 1> qtree;
        std::vector<Object> objects;
        
        Object o1; 
        Object o2;
        Object o3;
        Object o4;
        Object o5;
        Object o6;
        Object o7;
        Object o8;

        uint framePeriod_ = 100;
        bool isRunning_ = true;
    }; // class RenderWindow
} // namespace p2d

#endif