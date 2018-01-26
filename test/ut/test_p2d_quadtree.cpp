#include "gtest/gtest.h"

#include "p2d_quadtree.hpp"

TEST(TestQuadTree, QuadTreeWorks) {
    p2d::utility::QuadTreeNode<int, 10> qtree;

    EXPECT_TRUE(qtree.isLeafNode());

    qtree.subdivide();
    qtree[p2d::utility::SubQuad::NE].subdivide();

    EXPECT_FALSE(qtree.isLeafNode());
}