#ifndef P2D_VECTOR_HPP
#define P2D_VECTOR_HPP

#include <math.h>

#include "p2d_vector2.hpp"
#include "p2d_vector3.hpp"

namespace p2d { namespace math {
    typedef Vector2<float> Vector2f;
    typedef Vector2<int> Vector2i;
    typedef Vector3<float> Vector3f;
    typedef Vector3<int> Vector3i;

    float distance(const Vector2f& vec1, const Vector2f& vec2);
    float distance(const Vector2i& vec1, const Vector2i& vec2);
    float distance(const Vector3f& vec1, const Vector3f& vec2);
    float distance(const Vector3i& vec1, const Vector3i& vec2);
} // namespace math
} // namespace p2d

#endif