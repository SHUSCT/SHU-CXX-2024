#pragma once

#include <cstdint>

#include "03-build-and-link-against-libraries/System.hpp"

namespace shucxx2024
{
using int32_t = ::std::int32_t;

SHUCXX2024_API int32_t add(int32_t a, int32_t b);
SHUCXX2024_API int32_t sub(int32_t a, int32_t b);
}  // namespace shucxx2024