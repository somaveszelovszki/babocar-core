#include <babocar-core/ros/ros_convert.hpp>

#include <tf/tf.h>

#include <algorithm>

namespace bcr {
namespace detail {

radian_t quaternion_to_yaw(const geometry_msgs::Quaternion& quat) {
    tf::Quaternion q;
    tf::quaternionMsgToTF(quat, q);
    float64_t roll, pitch, yaw;
    tf::Matrix3x3(q).getRPY(roll, pitch, yaw);
    return radian_t(yaw);
}

geometry_msgs::Quaternion quaternion_from_yaw(radian_t angle) {
    return tf::createQuaternionMsgFromYaw(angle.get());
}

} // namespace detail

geometry_msgs::Pose ros_convert(const Pose& pose) {
    geometry_msgs::Pose result;
    result.position.x = static_cast<meter_t>(pose.pos.X).get();
    result.position.y = static_cast<meter_t>(pose.pos.Y).get();
    result.position.z = 0.0;
    result.orientation = detail::quaternion_from_yaw(pose.angle);
    return result;
}

Pose ros_convert(const geometry_msgs::Pose& pose) {
    Pose result;
    result.pos.Y = meter_t(pose.position.y);
    result.pos.X = meter_t(pose.position.x);
    result.angle = detail::quaternion_to_yaw(pose.orientation);
    return result;
}

geometry_msgs::Twist ros_convert(const Twist& twist) {
    geometry_msgs::Twist result;
    result.linear.x = static_cast<m_per_sec_t>(twist.X).get();
    result.linear.y = static_cast<m_per_sec_t>(twist.Y).get();
    result.linear.z = 0.0;
    result.angular.x = 0.0;
    result.angular.y = 0.0;
    result.angular.z = static_cast<rad_per_sec_t>(twist.ang_vel).get();
    return result;
}

Twist ros_convert(const geometry_msgs::Twist& twist) {
    Twist result;
    result.X = m_per_sec_t(twist.linear.x);
    result.Y = m_per_sec_t(twist.linear.y);
    result.ang_vel = rad_per_sec_t(twist.angular.z);
    return result;
}

nav_msgs::Odometry ros_convert(const Odometry& odom) {
    nav_msgs::Odometry result;
    // TODO header not filled out
    result.pose.pose = ros_convert(odom.pose);
    std::fill(result.pose.covariance.begin(), result.pose.covariance.end(), 0.0);
    result.twist.twist = ros_convert(odom.twist);
    std::fill(result.twist.covariance.begin(), result.twist.covariance.end(), 0.0);
    return result;
}

Odometry ros_convert(const nav_msgs::Odometry& odom) {
    Odometry result;
    result.pose = ros_convert(odom.pose.pose);
    result.twist = ros_convert(odom.twist.twist);
    return result;
}

} // namespace bcr

