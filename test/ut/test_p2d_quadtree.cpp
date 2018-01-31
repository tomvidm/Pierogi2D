#include "gtest/gtest.h"

#include "p2d_quadtree.hpp"
#include "p2d_utility.hpp"
#include "p2d_object.hpp"
#include "p2d_math.hpp"

#include <iostream>
#include <vector>

#include <stdlib.h>
#include <time.h>

TEST(TestQuadTree, QuadTreeWorks) {
    srand (time(NULL));

    p2d::utility::Rect<float> rect(0.f, 0.f, 639.f, 479.f);
    std::vector<std::shared_ptr<p2d::Object>> objectPtrs;
    p2d::utility::QuadTree<p2d::Object> qtreeRoot(rect);
    qtreeRoot.setCapacity(4);
    for (int i = 0; i < 20; i++) {
        p2d::math::Vector2f pos(static_cast<float>(rand() % 640),
                                static_cast<float>(rand() % 480));
        objectPtrs.push_back(std::make_shared<p2d::Object>());
        objectPtrs.back()->setPosition(pos);
        qtreeRoot.insert(objectPtrs.back());
    }

    EXPECT_EQ(qtreeRoot.getNumContainedObjects(), 20);
}