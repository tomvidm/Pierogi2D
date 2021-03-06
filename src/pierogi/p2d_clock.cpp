#include "p2d_clock.hpp"

namespace p2d {
    Clock::Clock() {
        reset();
    } // Clock

    void Clock::reset() {
        tickStart_ = SDL_GetTicks();
    } // reset

    Uint32 Clock::getElapsedTime() const {
        return SDL_GetTicks() - tickStart_;
    } // getElapsedTime

    float Clock::getElapsedSeconds() const {
        return static_cast<float>(SDL_GetTicks() - tickStart_)/1000.f;
    } // getElapsedSeconds
} // namespace p2d