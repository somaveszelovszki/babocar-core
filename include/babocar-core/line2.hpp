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

    Line2(const T& a, const T& b, const T& c)
        : a(a)
        , b(b)
        , c(c) {
        this->normalize();
    }

    Line2(const Point2<T>& p1, const Point2<T>& p2) {
        a = p1.Y - p2.Y;
        b = p2.X - p1.X;
        c = p1.X * p2.Y - p2.X * p1.Y;

        this->normalize();
    }

    /* @brief Casts line to another type.
     * @returns Line cast to another type.
     **/
    template <typename T2>
    operator Line2<T2>() const {
        return Line2<T2>(T2(a), T2(b), T2(c));
    }

    T normFactor() const {
        return std::sqrt(a * a + b * b);
    }

    void normalize() {
        const T factor = this->normFactor();
        a /= factor;
        b /= factor;
        c /= factor;
    }

    T getY(const T& x) const {
        return -(a / b) * x - (c / b);
    }

    T getX(const T& y) const {
        return -(b / a) * y - (c / a);
    }
    
};

typedef Line2<float32_t> Line2f;  // 32-bit floating point line.
typedef Line2<float64_t> Line2d;  // 64-bit floating point line.

} // namespace bcr

