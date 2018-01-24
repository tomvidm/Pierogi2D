#ifndef P2D_VECTOR3_HPP
#define P2D_VECTOR3_HPP

#include <math.h>

namespace p2d { namespace math {
    template <typename T>
    class Vector3 {
    public:
        Vector3();
        Vector3(const T& x, const T& y, const T& z);

        Vector3(const Vector3<T>& other);

        void operator += (const Vector3<T>& rhs);
        void operator *= (const T& rhs);

        Vector3 operator + (const Vector3<T>& rhs) const;
        Vector3 operator - (const Vector3<T>& rhs) const;
        Vector3 operator * (const T& rhs) const;

        float getMagnitudeSquared() const;
        float getMagnitude() const;

        T dot(const Vector3<T>& other) const;

        Vector3<float> getNormalized() const;

        inline T getX() const { return x_; }
        inline T getY() const { return y_; }
        inline T getZ() const { return z_; }
        inline T& getX() { return x_; }
        inline T& getY() { return y_; }
        inline T& getZ() { return z_; }
    private:
        T x_, y_, z_;
    }; // Vector3

    template <typename T>
    Vector3<T>::Vector3() 
    : x_(0), y_(0), z_(0) {
        ;
    } // constructor

    template <typename T>
    Vector3<T>::Vector3(const T& x, const T& y, const T& z) 
    : x_(x), y_(y), z_(z) {
        ;
    } // constructor

    template <typename T>
    Vector3<T>::Vector3(const Vector3<T>& other) 
    : x_(other.getX()), y_(other.getY()), z_(other.getZ()) {
        ;
    }

    template <typename T>
    void Vector3<T>::operator += (const Vector3<T>& rhs) {
        x_ += rhs.getX();
        y_ += rhs.getY();
        z_ += rhs.getZ();
    } // operatpr +=

    template <typename T>
    void Vector3<T>::operator *= (const T& rhs) {
        x_ *= rhs;
        y_ *= rhs;
        z_ *= rhs;
    } // operator *=

    template <typename T>
    Vector3<T> Vector3<T>::operator + (const Vector3<T>& rhs) const {
        return Vector3<T>(
            x_ + rhs.getX(),
            y_ + rhs.getY(),
            z_ + rhs.getZ()
        );
    } // operator +

    template <typename T>
    Vector3<T> Vector3<T>::operator - (const Vector3<T>& rhs) const {
        return Vector3<T>(
            x_ - rhs.getX(),
            y_ - rhs.getY(),
            z_ - rhs.getZ()
        );
    } // operator -

    template <typename T>
    Vector3<T> Vector3<T>::operator * (const T& rhs) const {
        return Vector3<T>(
            x_ * rhs,
            y_ * rhs,
            z_ * rhs
        );
    } // operator *

    template <typename T>
    float Vector3<T>::getMagnitudeSquared() const {
        return static_cast<float>((x_ * x_) + (y_ * y_) + (z_ * z_));
    } // getMagnitudeSquared

    template <typename T>
    float Vector3<T>::getMagnitude() const {
        return sqrtf(getMagnitudeSquared());
    } // getMagnitudeSquared

    template <typename T>
    T Vector3<T>::dot(const Vector3<T>& other) const {
        return (x_ * other.getX()) + (y_ * other.getY()) + (z_ * other.getZ());
    } // dot

    template <typename T>
    Vector3<float> Vector3<T>::getNormalized() const {
        return Vector3<float>((*this) * (1.f / getMagnitude()));
    } // getNormalized
} // namespace math
} // namespace p2d

#endif