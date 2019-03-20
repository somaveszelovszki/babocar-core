#pragma once

#include <babocar-core/units.hpp>
#include <babocar-core/pose.hpp>
#include <babocar-core/twist.hpp>
#include <babocar-core/odometry.hpp>

#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>

namespace bcr {

geometry_msgs::Pose ros_convert(const Pose& pose);
Pose ros_convert(const geometry_msgs::Pose& pose);

geometry_msgs::Twist ros_convert(const Twist& twist);
Twist ros_convert(const geometry_msgs::Twist& twist);

nav_msgs::Odometry ros_convert(const Odometry& odom);
Odometry ros_convert(const nav_msgs::Odometry& odom);

} // namespace bcr