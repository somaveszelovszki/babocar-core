#include <babocar-core/unit_utils.hpp>
#include <babocar-core/algorithm.hpp>

#include <iostream>

using namespace bcr;

constexpr distance_t a1 = centimeter_t(1.0f);
constexpr bcr::second_t a2 = second_t(1.0f);
constexpr speed_t sp = a1 / a2;

void test() {
    int32_t a_buf, b_buf;
    bcr::swap_xchg<int32_t> ints(&a_buf, &b_buf);
    int32_t *a = ints.set();
    *a = 3;
    ints.swap();
    const int32_t *b = ints.get();
    std::cout << *b << std::endl;   // prints: 3


    optional<m_per_sec_t> speed_opt = make_optional<m_per_sec_t>(1.0f);
    optional<m_per_sec_t> speed_opt2 = speed_opt;
    //optional<m_per_sec_t> speed_opt(1.0f), speed_opt2(speed_opt), speed_opt3(optional<m_per_sec_t>(2.0f));
    m_per_sec_t sp2 = *speed_opt;
}
