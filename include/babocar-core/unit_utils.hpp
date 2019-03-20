#pragma once

#include <babocar-core/numeric.hpp>
#include <babocar-core/units.hpp>

namespace bcr {
constexpr angle_t PI = radian_t(3.14159265358979323846);        	// Pi
constexpr angle_t PI_2 = PI / 2; // Pi / 2
constexpr angle_t PI_4 = PI / 4; // Pi / 4

/**
 * @brief Checks if given value equals the reference with the default epsilon tolerance.
 * @restrict Type must be a dimension class.
 * @tparam T Numeric type of the value, the reference and the epsilon tolerance.
 * @param value The value to compare to the reference.
 * @param ref The reference.
 */
template <typename T1, typename T2>
inline typename std::enable_if<T1::dim == T2::dim, bool>::type eq(const T1& value, const T2& ref) {
    return value.eq(ref);
}

template <typename T1, typename T2, typename T3>
inline typename std::enable_if<T1::dim == T2::dim && T1::dim == T3::dim, bool>::type eq(const T1& value, const T2& ref, const T3& eps) {
    return value.eq(ref, eps);
}

template <typename T>
inline typename std::enable_if<T::is_dim_class, bool>::type isZero(const T& value) {
    return value.isZero();
}

template <typename T, typename T_eps>
inline typename std::enable_if<T::dim == T_eps::dim, bool>::type isZero(const T& value, const T_eps& eps) {
    return value.isZero(eps);
}

/* @brief Calculates sine of given angle.
 * @restrict Type of the result value must be arithmetic.
 * @tparam T Type of the result value - 32-bit floating point number by default.
 * @param value The angle.
 * @returns The sine of the angle.
 **/
template <typename T = float32_t, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
inline T sin(const angle_t& value) {
    return static_cast<T>(sinf(radian_t(value).get())) ;
}

/* @brief Calculates arc-sine of given value.
 * @restrict Type of the value must be arithmetic.
 * @tparam T Type of the value.
 * @param value The value.+
 * @returns The arc-sine of the value.
 **/
template <typename T, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
inline angle_t asin(const T& value) {
    return radian_t(asinf(static_cast<float32_t>(value))) ;
}

/* @brief Calculates cosine of given angle.
 * @restrict Type of the result value must be arithmetic.
 * @tparam T Type of the result value - 32-bit floating point number by default.
 * @param value The angle.
 * @returns The cosine of the angle.
 **/
template <typename T = float32_t, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
inline T cos(const angle_t& value) {
    return static_cast<T>(cosf(radian_t(value).get())) ;
}

/* @brief Calculates arc-cosine of given value.
 * @restrict Type of the value must be arithmetic.
 * @tparam T Type of the value.
 * @param value The value.
 * @returns The arc-cosine of the value.
 **/
template <typename T, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
inline angle_t acos(const T& value) {
    return radian_t(acosf(static_cast<float32_t>(value))) ;
}

/* @brief Calculates tangent of given angle.
 * @restrict Type of the result value must be arithmetic.
 * @tparam T Type of the result value - 32-bit floating point number by default.
 * @param value The angle.
 * @returns The tangent of the angle.
 **/
template <typename T = float32_t, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
inline T tan(const angle_t& value) {
    return static_cast<T>(tanf(radian_t(value).get()));
}

/* @brief Calculates arc-tangent of given value.
 * @restrict Type of the value must be arithmetic.
 * @tparam T Type of the value.
 * @param value The value.
 * @returns The arc-tangent of the value.
 **/
template <typename T, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
inline angle_t atan(const T& value) {
    return radian_t(atanf(static_cast<float32_t>(value)));
}

inline angle_t normalize360(angle_t value) {
    static constexpr angle_t DEG_360 = 2 * PI;
    while(value >= DEG_360) {
        value -= DEG_360;
    }
    while(value < angle_t::ZERO()) {
        value += DEG_360;
    }
    return value;
}

inline angle_t normalize180(angle_t value) {
    while(value >= PI) {
        value -= PI;
    }
    while(value < angle_t::ZERO()) {
        value += PI;
    }
    return value;
}

inline bool eqWithOverflow360(angle_t value, angle_t ref, angle_t eps) {
    static constexpr angle_t DEG_360 = 2 * PI;
    return eq(value, ref, eps) || eq(value + DEG_360, ref, eps) || eq(value - DEG_360, ref, eps);
}

inline bool eqWithOverflow180(angle_t value, angle_t ref, angle_t eps) {
    return eq(value, ref, eps) || eq(value + PI, ref, eps) || eq(value - PI, ref, eps);
}

inline angle_t round45(angle_t value) {
    static constexpr angle_t EPS = PI_4 / 2;
    angle_t result;

    if (eqWithOverflow360(value, PI_4, EPS)) {
        result = PI_4;
    } else if (eqWithOverflow360(value, PI_2, EPS)) {
        result = PI_2;
    } else if (eqWithOverflow360(value, 3 * PI_4, EPS)) {
        result = 3 * PI_4;
    } else if (eqWithOverflow360(value, PI, EPS)) {
        result = PI;
    } else if (eqWithOverflow360(value, 5 * PI_4, EPS)) {
        result = 5 * PI_4;
    } else if (eqWithOverflow360(value, 3 * PI_2, EPS)) {
        result = 3 * PI_2;
    } else if (eqWithOverflow360(value, 7 * PI_4, EPS)) {
        result = 7 * PI_4;
    } else {
        result = angle_t::ZERO();
    }

    return result;
}

inline angle_t round90(angle_t value) {
    static constexpr angle_t EPS = PI_4;
    angle_t result;

    if (eqWithOverflow360(value, PI_2, EPS)) {
        result = PI_2;
    } else if (eqWithOverflow360(value, PI, EPS)) {
        result = PI;
    } else if (eqWithOverflow360(value, 3 * PI_2, EPS)) {
        result = 3 * PI_2;
    } else {
        result = angle_t::ZERO();
    }

    return result;
}

inline bool isMultipleOf90(angle_t value, angle_t eps) {

    return eqWithOverflow360(value, angle_t::ZERO(), eps)
        || eqWithOverflow360(value, PI_2, eps)
        || eqWithOverflow360(value, PI, eps)
        || eqWithOverflow360(value, 3 * PI_2, eps);
}

/* @brief Calculates square of the vector length using the Pythagorean theory.
 * @param a The length of the first leg of the triangle.
 * @param b The length of the other leg of the triangle.
 * @returns The length of the hypotenuse of the triangle.
 **/
inline distance_t pythag_square(distance_t a, distance_t b) {
    return centimeter_t(pythag_square(centimeter_t(a).get(), centimeter_t(b).get()));
}

/* @brief Calculates vector length using the Pythagorean theory.
 * @param a The length of the first leg of the triangle.
 * @param b The length of the other leg of the triangle.
 * @returns The length of the hypotenuse of the triangle.
 **/
inline distance_t pythag(distance_t a, distance_t b) {
    return centimeter_t(pythag(centimeter_t(a).get(), centimeter_t(b).get()));
}

/* @brief Calculates square of the vector length using the Pythagorean theory.
 * @param a The length of the first coordinate.
 * @param b The length of the second coordinate.
 * @param c The length of the third coordinate.
 * @returns The length of the vector.
 **/
inline distance_t pythag_square(distance_t a, distance_t b, distance_t c) {
    return centimeter_t(pythag_square(centimeter_t(a).get(), centimeter_t(b).get(), centimeter_t(c).get()));
}

/* @brief Calculates vector length using the Pythagorean theory.
 * @param a The length of the first coordinate.
 * @param b The length of the second coordinate.
 * @param c The length of the third coordinate.
 * @returns The length of the vector.
 **/
inline distance_t pythag(distance_t a, distance_t b, distance_t c) {
    return centimeter_t(pythag(centimeter_t(a).get(), centimeter_t(b).get(), centimeter_t(c).get()));
}

inline angle_t straighten(angle_t angle, angle_t eps) {
    if (eq(angle, PI_2, eps)) {
        angle = PI_2;
    } else if (eq(angle, PI, eps)) {
        angle = PI;
    } else if (eq(angle, 3 * PI_2, eps)) {
        angle = 3 * PI_2;
    } else if (angle.isZero(eps) || eq(angle, 2 * PI, eps)) {
        angle = angle_t::ZERO();
    }

    return angle;
}
} // namespace bcr

