#pragma once

#include <babocar-core/point2.hpp>
#include <vector>
#include <algorithm>
#include <limits>

namespace bcr {

class KMeans {
public:
    struct Group {
        Point2m center;
        std::vector<Point2m> members;

        Group() {}

        Group(const Point2m& center, std::vector<Point2m>&& members)
            : center(center)
            , members(std::move(members)) {}
    };

    KMeans(const std::vector<Point2m>& values_)
        : values_(values_) {}

    std::vector<Group> run(uint32_t numGroups) {
        std::vector<Group> groups(numGroups), prevGroups(numGroups);

        for(uint32_t i = 0; i < numGroups; ++i) {
            groups.emplace_back(this->values_[i], std::vector<Point2m>());
        }

        uint32_t iter = 1;
        do {
            prevGroups = groups;
            this->updateCenters(groups);
            this->fillGroups(groups);

        } while(iter++ < 2 || this->equalGroups(groups, prevGroups) || iter > 20);

        return groups;
    }

private:

    uint32_t getGroup(const std::vector<Group>& groups, const Point2m& value) {
        uint32_t minIdx = 0;
        meter_t minDist = groups[0].center.distance(value);
        for (uint32_t i = 1; i < groups.size(); ++i) {
            const meter_t dist = groups[i].center.distance(value);
            if (dist < minDist) {
                minDist = dist;
                minIdx = i;
            }
        }
        return minIdx;
    }

    void fillGroups(std::vector<Group>& groups) {
        for (Group& g : groups) {
            g.members.clear();
        }

        for (const Point2m& p : this->values_) {
            groups[this->getGroup(groups, p)].members.push_back(p);
        }
    }

    bool equalGroups(const std::vector<Group>& groups1, const std::vector<Group>& groups2) {
        bool eq = groups1.size() == groups2.size();
        if (eq) {
            for (uint32_t i = 0; i < groups1.size(); ++i) {
                const Group& g1 = groups1[i];
                const Group& g2 = groups2[i];

                if (!(eq = g1.members == g2.members)) {
                    break;
                }
            }
        }
        return eq;
    }

    void updateCenters(std::vector<Group>& groups) {
        for (Group& g : groups) {
            g.center = this->getCenter(g.members);
        }
    }

    Point2m getCenter(const std::vector<Point2m>& points) {
        Point2m center(meter_t::ZERO(), meter_t::ZERO());
        for(const Point2m& p : points) {
            center += p;
        }
        return center / points.size();
    }

    const std::vector<Point2m>& values_;
};
} // namespace bcr