#pragma once

#include <babocar-core/point2.hpp>
#include <babocar-core/units.hpp>

namespace bcr {
struct Twist {
    Point2mps speed;
    rad_per_sec_t ang_vel;
};
} // namespace bcr

