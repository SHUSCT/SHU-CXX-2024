#include "shucxx2024/Math.hpp"

namespace shucxx2024
{
double sqrt(double x)
{
    double result = 0.0;
    asm("sqrtsd %1, %0" : "=x"(result) : "x"(x));
    return result;
}
}  // namespace shucxx2024