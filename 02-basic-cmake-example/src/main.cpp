#include <string>

#include "02-basic-cmake-example/math/fabonacci.hpp"
#include "02-basic-cmake-example/utils/print.hpp"

int main()
{
    shucxx2024::print(TARGET_NAME " - Hello, World!");
    shucxx2024::print(std::to_string(shucxx2024::fabonacci_array(30)));
    shucxx2024::print(std::to_string(shucxx2024::fabonacci_recursion(30)));
    return 0;
}