#pragma once

#include <babocar-core/point2.hpp>
#include <babocar-core/units.hpp>

namespace bcr {
struct Twist {
    speed_t X;
    speed_t Y;
    angular_velocity_t ang_vel;
};
} // namespace bcr

