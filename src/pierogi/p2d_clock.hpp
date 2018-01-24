#ifndef P2D_TIMER_HPP
#define P2D_TIMER_HPP

#include "SDL.h"

namespace p2d {
    class Clock {
    public:
        Clock();
        void reset();
        Uint32 getElapsedTime() const;
        float getElapsedSeconds() const;
    private:
        Uint32 tickStart_;
    }; // class Clock
} // namespace p2d

#endif