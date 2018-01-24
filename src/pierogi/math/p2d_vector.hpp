#ifndef P2D_VECTOR_HPP
#define P2D_VECTOR_HPP

#include <math.h>

namespace p2d { namespace math {
    typedef unsigned int uint;

    template <typename T, uint D>
    class Vector {
    public:
        Vector();
        Vector(const Vector<T, D>& rhs);
        //~Vector();

        void operator += (const Vector<T, D>& rhs);
        void operator *= (const T& rhs);

        Vector<T, D> operator + (const Vector<T, D>& rhs) const;
        Vector<T, D> operator * (const T& rhs) const;

        T magnitudeSquared() const;

        // Vector<T, D> getNormalized() const;

        T operator [] (const uint& component) const;
        T& operator [] (const uint& component);
    private:
        uint dim_;
        T vals_[D];

    }; // class Vector

    template <typename T, uint D>
    Vector<T, D>::Vector() {
        dim_ = D;
        for (uint i = 0; i < dim_; i++) {
            vals_[i] = 0;
        }
    } // Constructor

    template <typename T, uint D>
    void Vector<T, D>::operator += (const Vector<T, D>& rhs) {
        for (uint i = 0; i < dim_; i++) {
            vals_[i] += rhs[i];
        }
    } // operator +=

    template <typename T, uint D>
    void Vector<T, D>::operator *= (const T& rhs) {
        for (uint i = 0; i < dim_; i++) {
            vals_[i] *= rhs;
        }
    } // operator *=

    template <typename T, uint D>
    Vector<T, D> Vector<T, D>::operator + (const Vector<T, D>& rhs) const {
        Vector<T, D> lhs(*this);
        for (uint i = 0; i < dim_; i++) {
            lhs[i] += rhs[i];
        }
        return lhs;
    } // operator +

    template <typename T, uint D>
    Vector<T, D> Vector<T, D>::operator * (const T& rhs) const {
        Vector<T, D> lhs(*this);
        for (uint i = 0; i < dim_; i++) {
            lhs[i] *= rhs;
        }
        return lhs;
    } // operator *

    template <typename T, uint D>
    T Vector<T, D>::magnitudeSquared() const {
        T result = 0;
        for (uint i = 0; i < dim_; i++)
        {
            result += (vals_[i] * vals_[i]);
        }
        return result;
    } // magnitudeSquared

    /*template <uint D>
    Vector<float, D> Vector<float, D>::getNormalized() const {
        return Vector<float, D>(*this) * (1.f / static_cast<float>(magnitudeSquared()));
    } // getNormalized*/

    template <typename T, uint D>
    T Vector<T, D>::operator [] (const uint& component) const {
        return vals_[component];
    } // operator []

    template <typename T, uint D>
    T& Vector<T, D>::operator [] (const uint& component) {
        return vals_[component];
    } // operator []
} // namespace math
} // namespace p2d

#endif