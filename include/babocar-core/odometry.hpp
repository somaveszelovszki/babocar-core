#pragma once

#include <babocar-core/pose.hpp>
#include <babocar-core/twist.hpp>

namespace bcr {
struct Odometry {
    Pose pose;
    Twist twist;
};
} // namespace bcr

