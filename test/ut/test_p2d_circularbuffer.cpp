#include "gtest/gtest.h"

#include "p2d_utility.hpp"

TEST(TestMath, CircularBuffer) {
    p2d::utility::CircularBuffer<int, 5> circBuf;
    EXPECT_EQ(circBuf[0], 0);

    circBuf.push(1);
    EXPECT_EQ(circBuf.head(), 0);
    circBuf.push(1);
    EXPECT_EQ(circBuf.head(), 0);
    circBuf.push(1);
    EXPECT_EQ(circBuf.head(), 0);
    circBuf.push(1);
    EXPECT_EQ(circBuf.head(), 0);
    circBuf.push(1);
    EXPECT_EQ(circBuf.head(), 1);
    circBuf.push(1);
    EXPECT_EQ(circBuf.head(), 1);

}