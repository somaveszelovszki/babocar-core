#pragma once

#include <babocar-core/line2.hpp>
#include <babocar-core/point2.hpp>

namespace bcr {

template <typename T>
T distance(const Line2<T>& line, const Point2<T>& point) {
    return bcr::abs(line.a * point.X + line.b * point.Y + line.c) / line.normFactor();
}

template <typename T>
T distanceNorm(const Line2<T>& lineNorm, const Point2<T>& point) {
    return bcr::abs(lineNorm.a * point.X + lineNorm.b * point.Y + lineNorm.c);
}

} // namespace bcr

