#pragma once

#include <babocar-core/units.hpp>

#include <ros/ros.h>

namespace bcr {

class RosNode : public ros::NodeHandle {
public:
    RosNode(const std::string& name, millisecond_t period)
        : name(name)
        , rate(second_t(1) / period) {}

    template <typename T>
    T getParameter(const std::string& key) const;

    const std::string name;
    ros::Rate rate;
};

template <typename T>
T RosNode::getParameter(const std::string& key) const {
    const std::string wholeKey = this->name + '/' + key;
    T param;
    if (!this->getParam(wholeKey, param)) {
        throw std::runtime_error("Error while retrieving parameter '" + wholeKey + "'.");
    }
    return param;
}
} // namespace bcr