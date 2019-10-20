#include <babocar-core/unit_utils.hpp>

#include <gtest/gtest.h>

using namespace bcr;

TEST(units, unit_convert) {
    constexpr millimeter_t mm(1000.0f);
    constexpr centimeter_t cm(100.0f);
    constexpr meter_t m(1.0f);
    constexpr kilometer_t km(0.001f);
    constexpr meter_t eps = meter_t(detail::COMMON_EQ_ABS_EPS);
    EXPECT_EQ(mm, mm);
    EXPECT_EQ(cm, cm);
    EXPECT_EQ(m, m);
    EXPECT_EQ(km, km);

    EXPECT_TRUE(bcr::eq(mm, mm, eps));
    EXPECT_TRUE(bcr::eq(mm, cm, eps));
    EXPECT_TRUE(bcr::eq(mm, m, eps));
    EXPECT_TRUE(bcr::eq(mm, km, eps));
    EXPECT_TRUE(bcr::eq(cm, cm, eps));
    EXPECT_TRUE(bcr::eq(cm, m, eps));
    EXPECT_TRUE(bcr::eq(cm, km, eps));
    EXPECT_TRUE(bcr::eq(m, m, eps));
    EXPECT_TRUE(bcr::eq(m, km, eps));
    EXPECT_TRUE(bcr::eq(km, km, eps));
}

TEST(units, compare) {
    constexpr millimeter_t mm(1);
    constexpr centimeter_t cm(1);

    EXPECT_TRUE(mm == mm);
    EXPECT_FALSE(mm != mm);
    EXPECT_FALSE(mm < mm);
    EXPECT_TRUE(mm <= mm);
    EXPECT_FALSE(mm > mm);
    EXPECT_TRUE(mm >= mm);

    EXPECT_FALSE(mm == cm);
    EXPECT_TRUE(mm != cm);
    EXPECT_TRUE(mm < cm);
    EXPECT_TRUE(mm <= cm);
    EXPECT_FALSE(mm > cm);
    EXPECT_FALSE(mm >= cm);
}

TEST(units, unit_div) {
    constexpr centimeter_t s(2.0f);
    constexpr second_t t(0.5f);
    constexpr m_per_sec_t v = s / t;
    EXPECT_NEAR(4.0f, static_cast<cm_per_sec_t>(v).get(), detail::COMMON_EQ_ABS_EPS);

    constexpr centimeter_t s2(2.0f);
    constexpr second_t t2(0.5f);
    constexpr m_per_sec_t v2 = s2 / t2;
    EXPECT_NEAR(0.04f, v2.get(), detail::COMMON_EQ_ABS_EPS);

    constexpr meter_t m(1);
    constexpr centimeter_t cm(1);
    EXPECT_NEAR(100.0f, m / cm, detail::COMMON_EQ_ABS_EPS);
}

TEST(units, unit_mul) {
    constexpr second_t t(0.5f);
    constexpr cm_per_sec_t v(4.0f);
    constexpr meter_t s = v * t;
    EXPECT_NEAR(2.0f, static_cast<centimeter_t>(s).get(), detail::COMMON_EQ_ABS_EPS);

    constexpr second_t t2(0.5f);
    constexpr m_per_sec_t v2(4.0f);
    constexpr meter_t s2 = v * t;
    EXPECT_NEAR(0.02f, s2.get(), detail::COMMON_EQ_ABS_EPS);
}
