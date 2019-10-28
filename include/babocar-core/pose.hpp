#pragma once

#include <babocar-core/point2.hpp>
#include <babocar-core/units.hpp>

namespace bcr {
struct Pose {
    Point2m pos;
    radian_t angle;
};
} // namespace bcr

