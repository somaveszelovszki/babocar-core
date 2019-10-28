#pragma once

#include "line2.hpp"
#include "point2.hpp"
#include "eq_solver.hpp"

#include <utility>
#include <limits>

namespace bcr {

template <typename T>
T distance(const Line2<T>& line, const Point2<T>& point) {
    return bcr::abs(line.a * point.X + line.b * point.Y + line.c) / line.normFactor();
}

template <typename T>
T distanceNorm(const Line2<T>& lineNorm, const Point2<T>& point) {
    return bcr::abs(lineNorm.a * point.X + lineNorm.b * point.Y + lineNorm.c);
}

template <typename T>
std::pair<Point2<T>, Point2<T>> lineCircle_intersection(const Line2<T>& line, const Point2<T>& circleCenter, const T& circleRadius) {
    // applies conversion between (0 = a*x + b*y + c) and (y = A*x + B)
    const T A = -line.a / line.b;
    const T B = -line.c / line.b;

    const T x_2 = 1 + A * A;
    const T x_1 = 2 * A * B - 2 * circleCenter.X - 2 * A * circleCenter.Y;
    const T x_0 = circleCenter.X * circleCenter.X + (B - circleCenter.Y) * (B - circleCenter.Y) - circleRadius * circleRadius;

    const std::pair<T, T> x1_2 = solve_quadratic(x_2, x_1, x_0);

    std::pair<Point2<T>, Point2<T>> result = {
        { std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::quiet_NaN() },
        { std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::quiet_NaN() }
    };

    if (!std::isnan(x1_2.first)) {
        result.first = { x1_2.first, line.getY(x1_2.first) };
    }

    if (!std::isnan(x1_2.second)) {
        result.second = { x1_2.second, line.getY(x1_2.second) };
    }

    return result;
}

template <typename T>
Point2<T> lineLine_intersection(const Line2<T>& line1, const Line2<T>& line2) {
    Point2<T> intersection = { std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity() };
    const T det = line2.a * line1.b - line1.a * line2.b;
    if (!isZero(det)) {
        intersection.X = (line1.c * line2.b - line2.c * line1.b) / det;
        intersection.Y = (line2.c * line1.a - line1.c * line2.a) / det;
    }
    return intersection;
}

} // namespace bcr

