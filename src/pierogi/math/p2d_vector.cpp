#include "p2d_vector.hpp"

namespace p2d { namespace math {
    float distance(const Vector2f& vec1, const Vector2f& vec2) {
        return (vec2 - vec1).getMagnitude();
    } // distance

    float distance(const Vector2i& vec1, const Vector2i& vec2) {
        return (vec2 - vec1).getMagnitude();
    } // distance

    float distance(const Vector3f& vec1, const Vector3f& vec2) {
        return (vec2 - vec1).getMagnitude();
    } // distance

    float distance(const Vector3i& vec1, const Vector3i& vec2) {
        return (vec2 - vec1).getMagnitude();
    } // distance
} // namespace math
} // namespace p2d