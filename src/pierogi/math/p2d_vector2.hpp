#ifndef P2D_VECTOR2_HPP
#define P2D_VECTOR2_HPP

#include <math.h>

namespace p2d { namespace math {
    template <typename T>
    class Vector2 {
    public:
        Vector2();
        Vector2(const T& x, const T& y);

        Vector2(const Vector2<T>& other);

        void operator += (const Vector2<T>& rhs);
        void operator *= (const T& rhs);

        Vector2 operator + (const Vector2<T>& rhs) const;
        Vector2 operator - (const Vector2<T>& rhs) const;
        Vector2 operator * (const T& rhs) const;

        float getMagnitudeSquared() const;
        float getMagnitude() const;

        T dot(const Vector2<T>& other) const;

        Vector2<float> getFloatified() const;
        Vector2<float> getNormalized() const;

        inline T getX() const { return x_; }
        inline T getY() const { return y_; }
        inline T& getX() { return x_; }
        inline T& getY() { return y_; }
        inline Vector2<T> getVectorX() const { return Vector2<T>(x_, T(0)); }
        inline Vector2<T> getVectorY() const { return Vector2<T>(T(0), y_); }
    private:
        T x_, y_;
    }; // Vector2

    template <typename T>
    Vector2<T>::Vector2() 
    : x_(0), y_(0) {
        ;
    } // constructor

    template <typename T>
    Vector2<T>::Vector2(const T& x, const T& y) 
    : x_(x), y_(y) {
        ;
    } // constructor

    template <typename T>
    Vector2<T>::Vector2(const Vector2<T>& other) 
    : x_(other.getX()), y_(other.getY()) {
        ;
    }

    template <typename T>
    void Vector2<T>::operator += (const Vector2<T>& rhs) {
        x_ += rhs.getX();
        y_ += rhs.getY();
    } // operatpr +=

    template <typename T>
    void Vector2<T>::operator *= (const T& rhs) {
        x_ *= rhs;
        y_ *= rhs;
    } // operator *=

    template <typename T>
    Vector2<T> Vector2<T>::operator + (const Vector2<T>& rhs) const {
        return Vector2<T>(
            x_ + rhs.getX(),
            y_ + rhs.getY()
        );
    } // operator +

    template <typename T>
    Vector2<T> Vector2<T>::operator - (const Vector2<T>& rhs) const {
        return Vector2<T>(
            x_ - rhs.getX(),
            y_ - rhs.getY()
        );
    } // operator -

    template <typename T>
    Vector2<T> Vector2<T>::operator * (const T& rhs) const {
        return Vector2<T>(
            x_ * rhs,
            y_ * rhs
        );
    } // operator *

    template <typename T>
    float Vector2<T>::getMagnitudeSquared() const {
        return static_cast<float>((x_ * x_) + (y_ * y_));
    } // getMagnitudeSquared

    template <typename T>
    float Vector2<T>::getMagnitude() const {
        return sqrtf(getMagnitudeSquared());
    } // getMagnitudeSquared

    template <typename T>
    T Vector2<T>::dot(const Vector2<T>& other) const {
        return (x_ * other.getX()) + (y_ * other.getY());
    } // dot

    template <typename T>
    Vector2<float> Vector2<T>::getFloatified() const {
        return Vector2<float>(static_cast<float>(x_),
                              static_cast<float>(y_));
    }

    template <typename T>
    Vector2<float> Vector2<T>::getNormalized() const {
        return Vector2<float>(getFloatified() * (1.f / getMagnitude()));
    } // getNormalized
} // namespace math
} // namespace p2d

#endif