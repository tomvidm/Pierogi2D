#include "gtest/gtest.h"

#include "p2d_rect.hpp"

TEST(TestRect, WorksWithVectors) {
    p2d::utility::Rect<float> rect(p2d::math::Vector2f(10.f, 10.f), 
                                   p2d::math::Vector2f(50.f, 50.f));
    p2d::math::Vector2f a(5.f, 5.f);
    p2d::math::Vector2f b(50.f, 50.f);

    EXPECT_FALSE(rect.contains(a));
    EXPECT_TRUE(rect.contains(b));

    rect *= 0.5f;

    EXPECT_FALSE(rect.contains(a));
    EXPECT_FALSE(rect.contains(b));

    rect += p2d::math::Vector2f(25.f, 25.f);

    EXPECT_TRUE(rect.contains(b));
}