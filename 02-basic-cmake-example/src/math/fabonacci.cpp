#include "02-basic-cmake-example/math/fabonacci.hpp"
#include <cstdint>

namespace shucxx2024
{
std::uint32_t fabonacci_recursion(std::size_t n)
{
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return fabonacci_recursion(n - 1) + fabonacci_recursion(n - 2);
}

std::uint32_t fabonacci_array(std::size_t n)
{
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    std::uint32_t fabonacci[2] = {0, 1};
    for (std::size_t i = 2; i <= n; ++i) {
        fabonacci[i % 2] = fabonacci[0] + fabonacci[1];
    }
    return fabonacci[n % 2];
}

}  // namespace shucxx2024