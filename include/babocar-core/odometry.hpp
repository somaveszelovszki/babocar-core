#pragma once

#include <babocar-core/pose.hpp>
#include <babocar-core/twist.hpp>
#include <babocar-core/unit_utils.hpp>

namespace bcr {
struct Odometry {
    Pose pose;
    Twist twist;

    void update(const millisecond_t d_time) {
        const radian_t d_angle = this->twist.ang_vel * d_time;
        const float64_t s = bcr::sin(d_angle / 2);
        const float64_t c = bcr::cos(d_angle / 2);

        this->twist.speed.rotate(s, c);
        this->pose.pos += this->twist.speed * d_time;
        this->twist.speed.rotate(s, c);
        this->pose.angle += d_angle;
    }
};
} // namespace bcr

