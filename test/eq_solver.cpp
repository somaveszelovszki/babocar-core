#include <babocar-core/eq_solver.hpp>

#include <gtest/gtest.h>

using namespace bcr;

TEST(eq_solver, solve_quadratic_0_solutions) {
    // 0 = (x - 2) ^ 2 + 1
    // no solutions
    const std::pair<float32_t, float32_t> result = bcr::solve_quadratic(1.0f, -4.0f, 5.0f);

    EXPECT_TRUE(std::isnan(result.first));
    EXPECT_TRUE(std::isnan(result.second));
}

TEST(eq_solver, solve_quadratic_1_solution) {
    // 0 = (x - 2) ^ 2
    // solution: 2
    const std::pair<float32_t, float32_t> result = bcr::solve_quadratic(1.0f, -4.0f, 4.0f);

    EXPECT_EQ(2.0f, result.first);
    EXPECT_TRUE(std::isnan(result.second));
}

TEST(eq_solver, solve_quadratic_2_solutions) {
    // 0 = (x - 2) ^ 2 - 1
    // solutions: 1, 3
    const std::pair<float32_t, float32_t> result = bcr::solve_quadratic(1.0f, -4.0f, 3.0f);

    EXPECT_EQ(3.0f, result.first);
    EXPECT_EQ(1.0f, result.second);
}