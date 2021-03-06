#ifndef P2D_RECT_HPP
#define P2D_RECT_HPP

#include "../math/p2d_math.hpp"

#include "SDL.h"

namespace p2d { namespace utility {
    using p2d::math::Vector2;

    template <typename T>
    class Rect {
    public:
        Rect();
        Rect(const Vector2<T>& pos, const Vector2<T>& siz);
        Rect(const float& x, const float& y, 
             const float& w, const float& h);

        bool contains(const Vector2<T>& point) const;

        void resize(const float& factor);
        void operator += (const Vector2<T>& rhs);
        void operator *= (const float& factor);

        inline Vector2<T> getSize() const { return size; }
        inline Vector2<T> getCenter() const { return origin + size * 0.5f; }

        Rect<T> Rect<T>::operator + (const Vector2<T>& rhs);
        Rect<T> Rect<T>::operator * (const float& factor);

        SDL_Rect getSDLRect() const;
    private:
        Vector2<T> origin;
        Vector2<T> size;
    }; // Rect

    template <typename T>
    Rect<T>::Rect(const Vector2<T>& pos, const Vector2<T>& siz) 
    : origin(pos), size(siz) {
        ;
    } // constructor

    template <typename T>
    Rect<T>::Rect(const float& x, const float& y, 
             const float& w, const float& h)
    : origin(Vector2<float>(x, y)),
      size(Vector2<float>(w, h)) {
        ;
    } // constructor

    template <typename T>
    Rect<T>::Rect()
    : origin(Vector2<T>()), size(Vector2<T>()) {
        ;
    } // constructor

    template <typename T>
    bool Rect<T>::contains(const Vector2<T>& point) const {
        return !((point.getX() <= origin.getX()) ||
                 (point.getY() <= origin.getY()) ||
                 (point.getX() > origin.getX() + size.getX()) ||
                 (point.getY() > origin.getY() + size.getY()));
    } // contains

    template <typename T>
    void Rect<T>::resize(const float& factor) {
        size *= factor;
    } // resize

    template <typename T>
    void Rect<T>::operator += (const Vector2<T>& rhs) {
        origin += rhs;
    } // resize

    template <typename T>
    void Rect<T>::operator *= (const float& factor) {
        size *= factor;
    } // operator *

    template <typename T>
    Rect<T> Rect<T>::operator + (const Vector2<T>& rhs) {
        Rect<T> copy = *this;
        copy += rhs;
        return copy;
    } // resize

    template <typename T>
    Rect<T> Rect<T>::operator * (const float& factor) {
        Rect<T> copy = *this;
        copy *= factor;
        return copy;
    }

    template <typename T>
    SDL_Rect Rect<T>::getSDLRect() const {
        SDL_Rect result;
        result.x = static_cast<int>(origin.getX());
        result.y = static_cast<int>(origin.getY());
        result.w = static_cast<int>(size.getX());
        result.h = static_cast<int>(size.getY());
        return result;
    }
} // namespace utility
} // namespace p2d

#endif