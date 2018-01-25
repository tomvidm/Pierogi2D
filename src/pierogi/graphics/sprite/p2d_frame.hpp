#ifndef P2D_FRAME_HPP
#define P2D_FRAME_HPP

#include "p2d_utility.hpp"

namespace p2d { namespace graphics {
    struct Frame {
        unsigned int duration;
        p2d::utility::FloatRect rect;
    }; // Frame
} // namespace graphics
} // namespace p2d

#endif