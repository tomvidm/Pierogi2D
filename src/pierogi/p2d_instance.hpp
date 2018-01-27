#ifndef P2D_INSTANCE_HPP
#define P2D_INSTANCE_HPP

#include "p2d_logger.hpp"
#include "p2d_clock.hpp"
#include "p2d_eventhandler.hpp"
#include "p2d_logger.hpp"
#include "p2d_typedefs.hpp"
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
        p2d::RenderWindow renderWindow;
        p2d::input::EventHandler eventHandler;
        p2d::debug::Logger* logger;

        uint framePeriod_ = 100;
        bool isRunning_;
    }; // class RenderWindow
} // namespace p2d

#endif