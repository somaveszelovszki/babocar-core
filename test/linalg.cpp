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

TEST(linalg, lineCircle_intersection_0_solutions) {
    const Line2f line(0.0f, -1.0f, 2.0f); // y = 0*x + 2
    const Point2f circleCenter(4.0f, 5.0f);
    const float32_t circleRadius = 2.0f;

    const std::pair<Point2f, Point2f> intersections = bcr::lineCircle_intersection(line, circleCenter, circleRadius);

    EXPECT_TRUE(std::isnan(intersections.first.X));
    EXPECT_TRUE(std::isnan(intersections.first.Y));
    EXPECT_TRUE(std::isnan(intersections.second.X));
    EXPECT_TRUE(std::isnan(intersections.second.Y));
}

TEST(linalg, lineCircle_intersection_1_solution_1) {
    const Line2f line(0.0f, -1.0f, 3.0f); // y = 0*x + 3
    const Point2f circleCenter(4.0f, 5.0f);
    const float32_t circleRadius = 2.0f;

    const std::pair<Point2f, Point2f> intersections = bcr::lineCircle_intersection(line, circleCenter, circleRadius);

    EXPECT_NEAR(4.0f, intersections.first.X, 0.0001f);
    EXPECT_NEAR(3.0f, intersections.first.Y, 0.0001f);
    EXPECT_TRUE(std::isnan(intersections.second.X));
    EXPECT_TRUE(std::isnan(intersections.second.Y));
}

TEST(linalg, lineCircle_intersection_2_solutions) {
    const Line2f line(0.0f, -1.0f, 5.0f); // y = 0*x + 5
    const Point2f circleCenter(4.0f, 5.0f);
    const float32_t circleRadius = 2.0f;

    const std::pair<Point2f, Point2f> intersections = bcr::lineCircle_intersection(line, circleCenter, circleRadius);

    EXPECT_NEAR(6.0f, intersections.first.X, 0.0001f);
    EXPECT_NEAR(5.0f, intersections.first.Y, 0.0001f);
    EXPECT_NEAR(2.0f, intersections.second.X, 0.0001f);
    EXPECT_NEAR(5.0f, intersections.second.Y, 0.0001f);
}

TEST(linalg, lineCircle_intersection_2_solutions_2) {
    const Line2d line(1.0, -1.0, 5.0); // y = x + 5
    const Point2d circleCenter(4.0, 9.0);
    const float64_t circleRadius = 2.0f;

    const std::pair<Point2d, Point2d> intersections = bcr::lineCircle_intersection(line, circleCenter, circleRadius);

    EXPECT_NEAR(4.0 + std::sqrt(2), intersections.first.X, 0.0001);
    EXPECT_NEAR(9.0 + std::sqrt(2), intersections.first.Y, 0.0001);
    EXPECT_NEAR(4.0 - std::sqrt(2), intersections.second.X, 0.0001);
    EXPECT_NEAR(9.0 - std::sqrt(2), intersections.second.Y, 0.0001);
}

TEST(linalg, lineLine_intersection) {
    const Line2d line1(1.0, -1.0, 5.0); // y = x + 5
    const Line2d line2(0.0, -1.0, 10.0); // y = 10

    const Point2d intersection = bcr::lineLine_intersection(line1, line2);

    EXPECT_NEAR(5.0, intersection.X, 0.0001);
    EXPECT_NEAR(10.0, intersection.Y, 0.0001);
}