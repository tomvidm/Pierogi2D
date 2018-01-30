#ifndef P2D_DRAWABLE_HPP
#define P2D_DRAWABLE_HPP

#include "SDL.h"

namespace p2d { namespace graphics {
    class Drawable {
    public:
        virtual void draw(SDL_Renderer* renderer) const;
    }; // Graphics
} // namespace p2d
} // namespace graphics

#endif