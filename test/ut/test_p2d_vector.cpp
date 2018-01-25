#include "gtest/gtest.h"

#include "p2d_vector.hpp"
#include "p2d_math.hpp"

TEST(TestMath, Vector2i_Arithmetic) {
    p2d::math::Vector2i vec2i_a(1, 2);  // a = [1, 2]
    p2d::math::Vector2i vec2i_b(2, 2);  // b = [2, 2]

    // a + b = [3, 4] - Pythagorean triplet is easy to test.
    EXPECT_EQ(vec2i_a.getMagnitudeSquared(), 5.f);      // |a|^2 = 5
    EXPECT_EQ(vec2i_b.getMagnitudeSquared(), 8.f);      // |b|^2 = 8
    EXPECT_EQ((vec2i_a + vec2i_b).getMagnitude(), 5.f); // |a + b| = 5

    // a dot b = 1*2 + 2*2 = 6
    EXPECT_EQ(vec2i_a.dot(vec2i_b), 6);

    // a/|a| = a_norm
    // Normalization only returns floating point components.
    // Magnitude and magnitude squared should be equal.
    // Currently uses quick and dirty float compare defined in p2d_math.hpp
    p2d::math::Vector2f vec2f_a_norm = vec2i_a.getNormalized();
    EXPECT_TRUE(p2d::math::floatComp(vec2f_a_norm.getMagnitude(), 1.f));
    EXPECT_TRUE(p2d::math::floatComp(vec2f_a_norm.getMagnitudeSquared(), 1.f));
}