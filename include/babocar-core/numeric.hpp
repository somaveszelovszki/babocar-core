#pragma once

#include <babocar-core/types.hpp>
#include <type_traits>
#include <cmath>

namespace bcr {

static constexpr float32_t COMMON_EQ_ABS_EPS = 0.00001f;    // Default absolute epsilon for equality check.

/**
 * @brief Gets minimum of the two values.
 * @param a The first value.
 * @param b The second value.
 * @returns The minimum of the two values.
 */
template <typename T>
inline T min(const T& a, const T& b) {
    return a < b ? a : b;
}

/**
 * @brief Gets absolute of the value.
 * @param value The value.
 * @returns The absolute of the value.
 */
template <typename T>
inline T abs(const T& value) {
    const T result = value >= T(0) ? value : -value;
    return result;
}

/**
 * @brief Gets maximum of the two values.
 * @param a The first value.
 * @param b The second value.
 * @returns The maximum of the two values.
 */
template <typename T>
inline T max(const T& a, const T& b) {
    return a > b ? a : b;
}

/**
 * @brief Gets average of the two values.
 * @param a The first value.
 * @param b The second value.
 * @returns The average of the two values.
 */
template <typename T>
inline T avg(const T& a, const T& b) {
    return T((a + b) / 2.0f);
}

/**
 * @brief Gets sign of the value.
 * @restrict Type must be arithmetic.
 * @param value The value.
 * @returns The sign of the value.
 */
template <typename T, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
inline Sign sgn(const T& value) {
    return value >= T(0) ? Sign::POSITIVE : Sign::NEGATIVE;
}

inline int32_t round(const float32_t value) {
    return static_cast<int32_t>(value + 0.5f);
}

/**
 * @brief Checks if a value is between the given boundaries.
 * @tparam T Type of the elements.
 * @param value The value to check.
 * @param b1 The first boundary.
 * @param b2 The second boundary.
 * @returns Boolean value indicating if the value is between the boundaries.
 */
template <typename T>
inline bool isBtw(const T& value, const T& b1, const T& b2) {
    return b2 >= b1 ? value >= b1 && value <= b2 : value >= b2 && value <= b1;
}

/**
 * @brief clamps value between the given boundaries.
 * @tparam T Type of the elements.
 * @param value The value to clamp.
 * @param b1 The first boundary.
 * @param b2 The second boundary.
 * @returns The clampd value.
 */
template <typename T>
inline T clamp(const T& value, const T& b1, const T& b2) {
    return b2 > b1 ? min(max(value, b1), b2) : min(max(value, b2), b1);
}

/**
 * @brief Checks if value is in a given range of the reference value.
 * @tparam T Numeric type of the value and the reference.
 * @param value The value to compare to the reference.
 * @param ref The reference value.
 * @param relErr The permitted relative error.
 */
template <typename T>
inline bool isInRange(const T& value, const T& ref, float32_t relErr) {
    return isBtw(value, static_cast<T>(ref * (1.0f - relErr)), static_cast<T>(ref * (1.0f + relErr)));
}

/**
 * @brief Maps value from from a given range to another.
 * @tparam S Numeric type of the source value and the source range boundaries.
 * @tparam R Numeric type of the result value and the result range boundaries.
 * @param value The value to map.
 * @param fromLow Lower boundary of the source range.
 * @param fromHigh Higher boundary of the source range.
 * @param toLow Lower boundary of the destination range.
 * @param toHigh Higher boundary of the destination range.
 * @returns The mapped value.
 */
template <typename S, typename R>
inline R map(const S& value, const S& fromLow, const S& fromHigh, const R& toLow, const R& toHigh) {
    return toLow + static_cast<R>((clamp(value, fromLow, fromHigh) - fromLow) * (toHigh - toLow) / (fromHigh - fromLow));
}

/**
 * @brief Checks if given value equals the reference with the default epsilon tolerance.
 * @restrict Type must be arithmetic.
 * @tparam T Numeric type of the value, the reference and the epsilon tolerance.
 * @param value The value to compare to the reference.
 * @param ref The reference.
 */
template <typename T>
inline typename std::enable_if<std::is_arithmetic<T>::value, bool>::type eq(const T& value, const T& ref) {
    static constexpr T eps(COMMON_EQ_ABS_EPS);
    return (value >= ref - eps) && (value <= ref + eps);
}

/**
 * @brief Checks if given value equals the reference with the given epsilon tolerance.
 * @tparam T Type of the value, the reference and the epsilon tolerance.
 * @param value The value to compare to the reference.
 * @param ref The reference.
 * @param eps The epsilon tolerance.
 */
template <typename T>
inline bool eq(const T& value, const T& ref, const T& eps) {
    return (value >= ref - eps) && (value <= ref + eps);
}

/**
 * @brief Checks if given value equals zero with the given epsilon tolerance.
 * @restrict Type must be arithmetic.
 * @tparam T Numeric type of the value, the reference and the epsilon tolerance.
 * @param value The value to compare to the reference.
 * @param eps The epsilon tolerance - 0.0001f by default.
 */
template <typename T, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
inline bool isZero(const T& value, T eps = static_cast<T>(COMMON_EQ_ABS_EPS)) {
    return eq(value, static_cast<T>(0), eps);
}

/**
 * @brief Calculates square of the vector length using the Pythagorean theory.
 * @restrict Type must be arithmetic.
 * @tparam T The type of the values.
 * @param a The length of the first leg of the triangle.
 * @param b The length of the other leg of the triangle.
 * @returns The length of the hypotenuse of the triangle.
 */
template <typename T, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
inline T pythag_square(const T& a, const T& b) {
    return a * a + b * b;
}

/**
 * @brief Calculates the hypotenuse of a triangle using the Pythagorean theory.
 * @restrict Type must be arithmetic.
 * @tparam T The type of the values.
 * @param a The length of the first leg of the triangle.
 * @param b The length of the other leg of the triangle.
 * @returns The length of the hypotenuse of the triangle.
 */
template <typename T, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
inline T pythag(const T& a, const T& b) {
    return static_cast<T>(sqrt(a * a + b * b));
}

/**
 * @brief Calculates square of the vector length using the Pythagorean theory.
 * @restrict Type must be arithmetic.
 * @tparam T The type of the values.
 * @param a The length of the first coordinate.
 * @param b The length of the second coordinate.
 * @param c The length of the third coordinate.
 * @returns The length of the vector.
 */
template <typename T, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
inline T pythag_square(const T& a, const T& b, const T& c) {
    return a * a + b * b + c * c;
}

/**
 * @brief Calculates vector length using the Pythagorean theory.
 * @restrict Type must be arithmetic.
 * @tparam T The type of the values.
 * @param a The length of the first coordinate.
 * @param b The length of the second coordinate.
 * @param c The length of the third coordinate.
 * @returns The length of the vector.
 */
template <typename T, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
inline T pythag(const T& a, const T& b, const T& c) {
    return static_cast<T>(sqrt(a * a + b * b + c * c));
}

/**
 * @brief Calculates power.
 * @param value
 * @param pow
 * @return
 */
template <typename T, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
inline T powerOf(const T& value, uint32_t pow) {
    T result(1);
    for (uint32_t i = 0; i < pow; ++i) {
        result *= value;
    }
    return result;
}

inline uint32_t add_overflow(uint32_t value, uint32_t incr, uint32_t exclusive_max) {
    value += incr;
    while(value >= exclusive_max) {
        value -= exclusive_max;
    }
    return value;
}

inline uint32_t sub_underflow(uint32_t value, uint32_t sub, uint32_t exclusive_max) {
    while(value < sub) {
        sub -= exclusive_max;
    }
    return value - sub;
}

inline uint32_t incr_overflow(uint32_t value, uint32_t exclusive_max) {
    return ++value == exclusive_max ? 0 : value;
}

inline uint32_t decr_underflow(uint32_t value, uint32_t exclusive_max) {
    return value-- == 0 ? exclusive_max - 1 : value;
}

} // namespace bcr

