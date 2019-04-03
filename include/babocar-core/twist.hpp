#pragma once

#include <babocar-core/point2.hpp>
#include <babocar-core/units.hpp>

namespace bcr {
struct Twist {
    m_per_sec_t X;
    m_per_sec_t Y;
    rad_per_sec_t ang_vel;
};
} // namespace bcr

