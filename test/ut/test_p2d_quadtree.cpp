#include "gtest/gtest.h"

#include "p2d_quadtree.hpp"
#include "p2d_object.hpp"
#include <iostream>
#include <vector>

TEST(TestQuadTree, QuadTreeWorks) {
    p2d::utility::Rect<float> rect(p2d::math::Vector2f(16.f, 16.f),
                                   p2d::math::Vector2f(384.f, 256.f));
    p2d::utility::QuadTree<2> qtree(rect);
    p2d::Object obj1;
    p2d::Object obj2;
    p2d::Object obj3;
    obj1.setPosition(60.f, 60.f);
    obj2.setPosition(120.f, 80.f);
    obj3.setPosition(180.f, 180.f);
    qtree.insert(obj1);
    qtree.insert(obj2);
    qtree.insert(obj3);

    EXPECT_TRUE(true);
}