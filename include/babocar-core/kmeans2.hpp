#pragma once

#include <babocar-core/point2.hpp>
#include <vector>
#include <algorithm>
#include <limits>

namespace bcr {

class KMeans2 {
public:
    static constexpr centimeter_t MAX_DIST = centimeter_t(10.0f);

    struct Group {
        std::vector<Point2m> members;
    };

    KMeans2(const std::vector<Point2m>& values_)
        : values_(values_) {}

    std::vector<Group> run() {
        std::vector<Group> groups;

        // Selects first pixel, finds pixels that are close to it, and adds them to group (removes them from the list of pixels).
        // Does the above until all the points have been added to a group.
        do {

            Group g;
            g.members.push_back(this->values_[this->values_.size() - 1]);
            this->values_.pop_back();

            std::vector<Point2m>::const_iterator it = this->values_.begin();
            while(it != this->values_.end()) {

                bool member = false;
                for (const Point2m& p : g.members) {
                    if (it->distance(p) < MAX_DIST) {
                        member = true;
                        g.members.push_back(*it);
                        it = this->values_.erase(it);
                        break;
                    }
                }

                if (!member) {
                    ++it;
                }
            }

        } while(!this->values_.empty());
    }

private:
    std::vector<Point2m> values_;
};
} // namespace bcr