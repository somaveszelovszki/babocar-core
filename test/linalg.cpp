#include <babocar-core/linalg.hpp>

#include <gtest/gtest.h>

using namespace bcr;

TEST(linalg, lineNorm) {
    Line2f line;
    line.a = 1.0f;
    line.b = 2.0f;
    line.c = 3.0f;

    Line2f line2 = line;
    line2.normalize();

    Point2f p(1.0f, 5.0f);
    EXPECT_FLOAT_EQ(bcr::distance(line, p), bcr::distance(line2, p));
}
