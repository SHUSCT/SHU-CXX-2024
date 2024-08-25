#include <iostream>

#include "02-basic-cmake-example/utils/print.hpp"

namespace shucxx2024
{
void print(std::string_view str)
{
    std::cout << str << std::endl;
}
}  // namespace shucxx2024