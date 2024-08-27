#include <functional>

#include "03-build-and-link-against-libraries/Math.hpp"

namespace shucxx2024
{
int32_t add(int32_t a, int32_t b)
{
    return ::std::plus<>{}(a, b);
};

int32_t sub(int32_t a, int32_t b)
{
    return ::std::minus<>{}(a, b);
};
}  // namespace shucxx2024