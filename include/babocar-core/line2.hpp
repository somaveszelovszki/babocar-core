#pragma once

#include <babocar-core/point2.hpp>

#include <cmath>

namespace bcr {
/** @brief Template implementation for 2-dimensional lines.
 * @tparam T Numeric type of the coordinates.
 */
template <typename T> struct Line2 {
    /** @brief a*x + b*y + c = 0
    */
    T a, b, c;

    /* @brief Constructor - does not initializes coordinates.
     **/
    Line2() {}

    Line2(const Point2<T>& p1, const Point2<T>& p2) {
        this->a = p1.Y - p2.Y;
        this->b = p2.X - p1.X;
        this->c = p1.X * p2.Y - p2.X * p1.Y;

        this->normalize();
    }

    /* @brief Casts line to another type.
     * @returns Line cast to another type.
     **/
    template <typename T2>
    operator Line2<T2>() const {
        return Line2<T2>(T2(this->X), T2(this->Y));
    }

    T normFactor() const {
        return std::sqrt(this->a * this->a + this->b * this->b);
    }

    void normalize() {
        const T factor = this->normFactor();
        this->a /= factor;
        this->b /= factor;
        this->c /= factor;
    }
    
};

typedef Line2<float32_t>   Line2f;  // 32-bit floating point line.

} // namespace bcr

