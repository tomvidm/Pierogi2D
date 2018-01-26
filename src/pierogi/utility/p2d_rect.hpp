#ifndef P2D_RECT_HPP
#define P2D_RECT_HPP

#include "../math/p2d_math.hpp"

namespace p2d { namespace utility {
    using p2d::math::Vector2;

    template <typename T>
    class Rect {
    public:
        Rect();
        Rect(const Vector2<T>& pos, const Vector2<T>& siz);

        bool contains(const Vector2<T>& point);
    private:
        Vector2<T> origin;
        Vector2<T> size;
    }; // Rect

    template <typename T>
    Rect<T>::Rect(const Vector2<T>& pos, const Vector2<T>& siz) 
    : origin(pos), size(siz) {
        ;
    }

    template <typename T>
    Rect<T>::Rect()
    : origin(Vector2<T>()), size(Vector2<T>()) {
        ;
    }

    template <typename T>
    bool Rect<T>::contains(const Vector2<T>& point) {
        return !((point.getX() < origin.getX()) ||
                 (point.getY() < origin.getY()) ||
                 (point.getX() > origin.getX() + size.getX()) ||
                 (point.getY() > origin.getY() + size.getY()));
    }
} // namespace utility
} // namespace p2d

#endif