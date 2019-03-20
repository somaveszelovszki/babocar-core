#pragma once

#include <babocar-core/point2.hpp>
#include <babocar-core/units.hpp>

namespace bcr {
struct Pose : public Point2<distance_t> {
    angle_t angle;
};
} // namespace bcr

