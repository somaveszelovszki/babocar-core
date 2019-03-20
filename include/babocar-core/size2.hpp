#pragma once

#include <babocar-core/types.hpp>

namespace bcr {
/* @brief Template implementation for 2-dimensional sizes.
 * @tparam T Numeric type of the coordinates.
 **/
template <typename T> struct Size2 {
    /* @brief The X size component.
     **/
    T X;

    /* @brief The Y size component.
     **/
    T Y;

    /* @brief Constructor - does not initializes size components.
     **/
    Size2() {}

    /* @brief Casts size to another type.
     * @returns Size cast to another type.
     **/
    template <typename T2>
    operator Size2<T2>() const {
        return Size2<T2>(T2(this->X), T2(this->Y));
    }

    /* @brief Checks if two sizes are equal
     * @param other The other size object.
     * @returns Boolean value indicating if the two sizes are equal.
     **/
    bool operator==(const Size2<T>& other) const {
        return this->X == other.X && this->Y == other.Y;
    }

    /* @brief Checks if two sizes are not equal
     * @param other The other size object.
     * @returns Boolean value indicating if the two sizes are not equal.
     **/
    bool operator!=(const Size2<T>& other) const {
        return this->X != other.X || this->Y != other.Y;
    }

    auto area() const -> decltype(T * T) {
        return this->X * this-> Y;
    }
    
};

typedef Size2<float32_t>   Size2f;  // 32-bit floating point size.

} // namespace bcr

