#ifndef P2D_FRAMESEQUENCE_HPP
#define P2D_FRAMESEQUENCE_HPP

#include "p2d_frame.hpp"

#include <vector>

namespace p2d { namespace graphics {
    class FrameSequence {
    public:
        
    private:
        unsigned int currentFrameIndex;
        unsigned int sequenceLength;

        std::vector<Frame> frameVector;
    }; // FrameSequence
} // namespace graphics
} // namespace p2d

#endif