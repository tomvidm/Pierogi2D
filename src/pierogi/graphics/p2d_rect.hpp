#ifndef P2D_RECT_HPP
#define P2D_RECT_HPP

#include "p2d_math.hpp"

namespace p2d { namespace graphics {
    using p2d::math::Vector2;

    template <typename T>
    class Rect {
    public:
        Rect(const Vector2<T>& pos, const Vector2<T>& siz);
    private:
        Vector2<T> origin;
        Vector2<T> size;
    }; // Rect

    template <typename T>
    Rect<T>::Rect(const Vector2<T>& pos, const Vector2<T>& siz) 
    : origin(pos), size(siz) {
        ;
    }
} // namespace graphics
} // namespace p2d

#endif