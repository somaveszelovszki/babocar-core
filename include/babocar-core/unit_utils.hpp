#pragma once

#include <babocar-core/numeric.hpp>
#include <babocar-core/units.hpp>

namespace bcr {
constexpr radian_t PI = radian_t(3.14159265358979323846);        	// Pi
constexpr radian_t PI_2 = PI / 2; // Pi / 2
constexpr radian_t PI_4 = PI / 4; // Pi / 4

/**
 * @brief Gets absolute of the value.
 * @param value The value.
 * @returns The absolute of the value.
 */
template <typename T>
inline typename std::enable_if<is_unit<T>::value, T>::type abs(const T& value) {
    return value >= T::ZERO() ? value : -value;
}

/**
 * @brief Checks if value is NaN.
 * @param value The value.
 * @returns Boolean value indicating if the value is NaN.
 */
template <typename T>
inline typename std::enable_if<is_unit<T>::value, bool>::type isnan(const T& value) {
    return std::isnan(value.template get<true>());
}

/**
 * @brief Checks if value is infinity.
 * @param value The value.
 * @returns Boolean value indicating if the value is infinity.
 */
template <typename T>
inline typename std::enable_if<is_unit<T>::value, bool>::type isinf(const T& value) {
    return std::isinf(value.template get<true>());
}

/**
 * @brief Gets sign of the value.
 * @restrict Type must be a unit class.
 * @param value The value.
 * @returns The sign of the value.
 */
template <typename T, class = typename std::enable_if<is_unit<T>::value>::type>
inline typename std::enable_if<is_unit<T>::value, Sign>::type sgn(const T& value) {
    return value >= T::ZERO() ? Sign::POSITIVE : Sign::NEGATIVE;
}

/**
 * @brief Checks if given value equals the reference with the default epsilon tolerance.
 * @restrict Types must be unit classes of the same dimension.
 * @tparam T Numeric type of the value, the reference and the epsilon tolerance.
 * @param value The value to compare to the reference.
 * @param ref The reference.
 */
template <typename T1, typename T2>
inline typename std::enable_if<T1::is_dim_class && T2::is_dim_class && T1::dim == T2::dim, bool>::type eq(const T1& value, const T2& ref) {
    return bcr::eq(value, ref, T1(bcr::detail::COMMON_EQ_ABS_EPS, nullptr));
}

/**
 * @brief Checks if given value equals zero with the given epsilon tolerance.
 * @restrict Type must be a unit class.
 * @tparam T Numeric type of the value, the reference and the epsilon tolerance.
 * @param value The value to compare to the reference.
 * @param eps The epsilon tolerance - 0.0001f by default.
 */
template <typename T1, typename T2>
inline typename std::enable_if<T1::is_dim_class && T2::is_dim_class && T1::dim == T2::dim, bool>::type isZero(const T1& value, const T2 eps) {
    return bcr::eq(value, T1::ZERO(), eps);
}

/**
 * @brief Checks if given value equals zero with the given epsilon tolerance.
 * @restrict Type must be a unit class.
 * @tparam T Numeric type of the value, the reference and the epsilon tolerance.
 * @param value The value to compare to the reference.
 * @param eps The epsilon tolerance - 0.0001f by default.
 */
template <typename T>
inline typename std::enable_if<is_unit<T>::value, bool>::type isZero(const T& value) {
    return bcr::eq(value, T::ZERO());
}

/**
 * @brief Calculates the hypotenuse of a triangle using the Pythagorean theory.
 * @restrict Type must be a unit class.
 * @tparam T The type of the values.
 * @param a The length of the first leg of the triangle.
 * @param b The length of the other leg of the triangle.
 * @returns The length of the hypotenuse of the triangle.
 */
template <typename T1, typename T2>
inline typename std::enable_if<T1::is_dim_class && T2::is_dim_class && T1::dim == T2::dim, T1>::type pythag(const T1& a, const T2& b) {
    const unit_storage_type _a = a.template get<true>();
    const unit_storage_type _b = static_cast<T1>(b).template get<true>();
    return T1(std::sqrt(_a * _a + _b * _b), nullptr);
}

/**
 * @brief Calculates vector length using the Pythagorean theory.
 * @restrict Type must be a unit class.
 * @tparam T The type of the values.
 * @param a The length of the first coordinate.
 * @param b The length of the second coordinate.
 * @param c The length of the third coordinate.
 * @returns The length of the vector.
 */
template <typename T1, typename T2, typename T3>
inline typename std::enable_if<T1::is_dim_class && T2::is_dim_class && T3::is_dim_class && T1::dim == T2::dim && T1::dim == T3::dim, T1>::type pythag(const T1& a, const T2& b, const T3& c) {
    const unit_storage_type _a = a.template get<true>();
    const unit_storage_type _b = static_cast<T1>(b).template get<true>();
    const unit_storage_type _c = static_cast<T1>(c).template get<true>();
    return T1(std::sqrt(_a * _a + _b * _b + _c * _c), nullptr);
}

/* @brief Calculates sine of given angle.
 * @param value The angle.
 * @returns The sine of the angle.
 **/
inline unit_storage_type sin(const radian_t& value) {
    return std::sin(value.template get<true>());
}

/* @brief Calculates arc-sine of given value.
 * @param value The value.+
 * @returns The arc-sine of the value.
 **/
inline radian_t asin(unit_storage_type value) {
    return radian_t(std::asin(value)) ;
}

/* @brief Calculates cosine of given angle.
 * @param value The angle.
 * @returns The cosine of the angle.
 **/
inline unit_storage_type cos(const radian_t& value) {
    return std::cos(value.template get<true>()) ;
}

/* @brief Calculates arc-cosine of given value.
 * @param value The value.
 * @returns The arc-cosine of the value.
 **/
inline radian_t acos(unit_storage_type value) {
    return radian_t(std::acos(value)) ;
}

/* @brief Calculates tangent of given angle.
 * @param value The angle.
 * @returns The tangent of the angle.
 **/
inline unit_storage_type tan(const radian_t& value) {
    return std::tan(value.template get<true>());
}

/* @brief Calculates arc-tangent of given value.
 * @param value The value.
 * @returns The arc-tangent of the value.
 **/
inline radian_t atan(unit_storage_type value) {
    return radian_t(std::atan(value));
}

template <typename T>
inline typename std::enable_if<std::is_arithmetic<T>::value, radian_t>::type atan2(const T& y, const T& x) {
    return radian_t(std::atan2(static_cast<unit_storage_type>(y), static_cast<unit_storage_type>(x)));
}

template <typename T1, typename T2>
inline typename std::enable_if<T1::is_dim_class && T2::is_dim_class && T1::dim == T2::dim, radian_t>::type atan2(const T1& y, const T2& x) {
    return radian_t(std::atan2(y.template get<true>(), static_cast<T1>(x).template get<true>()));
}

inline radian_t normalize360(radian_t value) {
    static constexpr radian_t DEG_360 = 2 * PI;
    while(value >= DEG_360) {
        value -= DEG_360;
    }
    while(value < radian_t::ZERO()) {
        value += DEG_360;
    }
    return value;
}

inline radian_t normalize180(radian_t value) {
    while(value >= PI) {
        value -= PI;
    }
    while(value < radian_t::ZERO()) {
        value += PI;
    }
    return value;
}

inline bool eqWithOverflow360(radian_t value, radian_t ref, radian_t eps) {
    static constexpr radian_t DEG_360 = 2 * PI;
    return bcr::eq(value, ref, eps) || bcr::eq(value + DEG_360, ref, eps) || bcr::eq(value - DEG_360, ref, eps);
}

inline bool eqWithOverflow180(radian_t value, radian_t ref, radian_t eps) {
    return bcr::eq(value, ref, eps) || bcr::eq(value + PI, ref, eps) || bcr::eq(value - PI, ref, eps);
}

inline radian_t round45(radian_t value) {
    static constexpr radian_t EPS = PI_4 / 2;
    radian_t result;

    if (bcr::eqWithOverflow360(value, PI_4, EPS)) {
        result = PI_4;
    } else if (bcr::eqWithOverflow360(value, PI_2, EPS)) {
        result = PI_2;
    } else if (bcr::eqWithOverflow360(value, 3 * PI_4, EPS)) {
        result = 3 * PI_4;
    } else if (bcr::eqWithOverflow360(value, PI, EPS)) {
        result = PI;
    } else if (bcr::eqWithOverflow360(value, 5 * PI_4, EPS)) {
        result = 5 * PI_4;
    } else if (bcr::eqWithOverflow360(value, 3 * PI_2, EPS)) {
        result = 3 * PI_2;
    } else if (bcr::eqWithOverflow360(value, 7 * PI_4, EPS)) {
        result = 7 * PI_4;
    } else {
        result = radian_t::ZERO();
    }

    return result;
}

inline radian_t round90(radian_t value) {
    static constexpr radian_t EPS = PI_4;
    radian_t result;

    if (bcr::eqWithOverflow360(value, PI_2, EPS)) {
        result = PI_2;
    } else if (bcr::eqWithOverflow360(value, PI, EPS)) {
        result = PI;
    } else if (bcr::eqWithOverflow360(value, 3 * PI_2, EPS)) {
        result = 3 * PI_2;
    } else {
        result = radian_t::ZERO();
    }

    return result;
}

inline bool isMultipleOf90(radian_t value, radian_t eps) {

    return eqWithOverflow360(value, radian_t::ZERO(), eps)
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
    return centimeter_t(pythag_square(centimeter_t(a).template get<true>(), centimeter_t(b).template get<true>()));
}

/* @brief Calculates vector length using the Pythagorean theory.
 * @param a The length of the first leg of the triangle.
 * @param b The length of the other leg of the triangle.
 * @returns The length of the hypotenuse of the triangle.
 **/
inline distance_t pythag(distance_t a, distance_t b) {
    return centimeter_t(pythag(centimeter_t(a).template get<true>(), centimeter_t(b).template get<true>()));
}

/* @brief Calculates square of the vector length using the Pythagorean theory.
 * @param a The length of the first coordinate.
 * @param b The length of the second coordinate.
 * @param c The length of the third coordinate.
 * @returns The length of the vector.
 **/
inline distance_t pythag_square(distance_t a, distance_t b, distance_t c) {
    return centimeter_t(pythag_square(centimeter_t(a).template get<true>(), centimeter_t(b).template get<true>(), centimeter_t(c).template get<true>()));
}

/* @brief Calculates vector length using the Pythagorean theory.
 * @param a The length of the first coordinate.
 * @param b The length of the second coordinate.
 * @param c The length of the third coordinate.
 * @returns The length of the vector.
 **/
inline distance_t pythag(distance_t a, distance_t b, distance_t c) {
    return centimeter_t(pythag(centimeter_t(a).template get<true>(), centimeter_t(b).template get<true>(), centimeter_t(c).template get<true>()));
}

inline radian_t straighten(radian_t angle, radian_t eps) {
    if (bcr::eq(angle, PI_2, eps)) {
        angle = PI_2;
    } else if (bcr::eq(angle, PI, eps)) {
        angle = PI;
    } else if (bcr::eq(angle, 3 * PI_2, eps)) {
        angle = 3 * PI_2;
    } else if (bcr::isZero(angle, eps) || bcr::eq(angle, 2 * PI, eps)) {
        angle = radian_t::ZERO();
    }

    return angle;
}
} // namespace bcr

