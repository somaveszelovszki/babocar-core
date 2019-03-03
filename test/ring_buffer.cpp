#include <babocar-core/container/ring_buffer.hpp>

#include <gtest/gtest.h>
#include <iostream>
#include "ros/ros.h"

using namespace bcr;

TEST(ring_buffer, constructor_initializer_list) {
    ring_buffer<int32_t, 3> v = { 1, 2, 3 };
    ASSERT_EQ(3, v.capacity());
    ASSERT_EQ(3, v.size());

    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(2, v[1]);
    EXPECT_EQ(3, v[2]);
}

TEST(ring_buffer, append) {
    ring_buffer<int32_t, 3> v;
    ASSERT_EQ(0, v.size());
    EXPECT_EQ(3, v.capacity());

    v.append(1);
    v.append(2);
    v.append(3);
    ASSERT_TRUE(v.full());
    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(2, v[1]);
    EXPECT_EQ(3, v[2]);

    v.append(4);
    ASSERT_TRUE(v.full());
    EXPECT_EQ(2, v[0]);
    EXPECT_EQ(3, v[1]);
    EXPECT_EQ(4, v[2]);

    v.clear();
    ASSERT_TRUE(v.empty());
}
