#include "p2d_clock.hpp"

namespace p2d {
    Clock::Clock() {
        reset();
    } // Clock

    void Clock::reset() {
        tickStart_ = SDL_GetTicks();
    } // void reset

    Uint32 Clock::getElapsedTime() {
        return SDL_GetTicks() - tickStart_;
    } // Uint32 getElapsedTime
} // namespace p2d