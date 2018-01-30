#include "gtest/gtest.h"

#include "quadtreenode.hpp"
#include "p2d_utility.hpp"
#include "p2d_object.hpp"
#include "p2d_math.hpp"

#include <iostream>
#include <vector>

TEST(TestQuadTree, QuadTreeWorks) {
    p2d::utility::Rect<float> rect(0.f, 0.f, 640.f, 480.f);
    p2d::math::Vector2f v(300.f, 300.f);
    p2d::utility::QuadTreeNode<p2d::Object> qtreeRoot(rect);
    qtreeRoot.findNextQuadContaining(v)->subdiv();
    EXPECT_TRUE(true);
}