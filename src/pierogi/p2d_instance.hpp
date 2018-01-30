#ifndef P2D_INSTANCE_HPP
#define P2D_INSTANCE_HPP

#include "p2d_logger.hpp"
#include "p2d_clock.hpp"
#include "p2d_compiletimeconstants.hpp"
#include "p2d_eventhandler.hpp"
#include "p2d_logger.hpp"
#include "p2d_typedefs.hpp"
#include "p2d_utility.hpp"
#include "p2d_object.hpp"
#include "p2d_window.hpp"
#include "quadtreenode.hpp"

#include <memory>

namespace p2d {
    using p2d::utility::QuadTreeNode;
    using p2d::Object;

    class Instance {
    public:
        Instance();
        ~Instance();

        void run();

        inline bool isRunning() const { return isRunning_; }
    private:
        bool init();
        void handleInput();
        void update(float dt);
        void render();
        p2d::RenderWindow renderWindow;
        p2d::input::EventHandler eventHandler;
        p2d::debug::Logger* logger;

        std::shared_ptr<QuadTreeNode<Object>> rootNodePtr;
        p2d::input::Event event;
        p2d::Clock clk;
        math::Vector2f mousePos;

        std::vector<std::shared_ptr<Object>> objectPtrs; // Use smart pointers to avoid stupid reallocation bug.

        uint framePeriod_ = 100;
        bool isRunning_ = true;
    }; // class RenderWindow
} // namespace p2d

#endif