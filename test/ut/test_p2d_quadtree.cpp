#include "gtest/gtest.h"

#include "p2d_quadtree.hpp"
#include <iostream>

TEST(TestQuadTree, QuadTreeWorks) {
    p2d::utility::QuadTreeNode<int, 10> qtree;
    p2d::math::Vector2<float> point(75.f, 75.f);
    qtree.setRectCoverage(p2d::utility::Rect<float>(p2d::math::Vector2<float>(0.f, 0.f),
                                                    p2d::math::Vector2<float>(100.f, 100.f)));
    EXPECT_TRUE(qtree.coversPoint(point));
    EXPECT_TRUE(qtree.isLeafNode());

    qtree.subdivide();
    qtree[p2d::utility::SubQuad::NE].subdivide();

    EXPECT_FALSE(qtree[p2d::utility::SubQuad::NW].coversPoint(point));
    EXPECT_FALSE(qtree[p2d::utility::SubQuad::NE].coversPoint(point));
     EXPECT_TRUE(qtree[p2d::utility::SubQuad::SE].coversPoint(point));
    EXPECT_FALSE(qtree[p2d::utility::SubQuad::SW].coversPoint(point));

    EXPECT_EQ(&qtree[p2d::utility::SubQuad::SE], &qtree.findNodeContaining(point));

    EXPECT_FALSE(qtree.isLeafNode());
}