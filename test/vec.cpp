#include <babocar-core/container/vec.hpp>

#include <gtest/gtest.h>
#include <iostream>

using namespace bcr;

TEST(vec, constructor_initializer_list) {
    vec<int32_t, 3> v = { 1, 2, 3 };
    ASSERT_EQ(3, v.capacity());
    ASSERT_EQ(3, v.size());

    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(2, v[1]);
    EXPECT_EQ(3, v[2]);
}

TEST(vec, append_remove_insert) {
    vec<int32_t, 3> v;
    ASSERT_EQ(0, v.size());
    EXPECT_EQ(3, v.capacity());

    v.append(1);
    v.append(2);
    v.append(3);
    v.remove(v.begin() + 1);
    ASSERT_EQ(2, v.size());
    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(3, v[1]);

    v.insert(v.begin(), 4);
    ASSERT_EQ(3, v.size());
    EXPECT_EQ(4, v[0]);
    EXPECT_EQ(1, v[1]);
    EXPECT_EQ(3, v[2]);
}

TEST(vec, find) {
    vec<int32_t, 3> v = { 1, 2, 3 };
    vec<int32_t, 3>::const_iterator it = v.find(1);
    ASSERT_NE(v.end(), it);
    EXPECT_EQ(1, *it);

    it = v.find(2);
    ASSERT_NE(v.end(), it);
    EXPECT_EQ(2, *it);

    it = v.find(3);
    ASSERT_NE(v.end(), it);
    EXPECT_EQ(3, *it);

    it = v.find(4);
    EXPECT_EQ(v.end(), it);
}
