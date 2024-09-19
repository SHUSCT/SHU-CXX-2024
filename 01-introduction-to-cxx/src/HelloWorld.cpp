// "Include a header" means to copy the content of the header file to the source
// file.
#include "shucxx2024/HelloWorld.hpp"

// The C++ Standard Library header file `iostream` contains declarations for
// the input/output stream objects such as `std::cout` and `std::cin`.
#include <iostream>

namespace shucxx2024
{
// Function definition for `sayHello`.
void sayHello()
{
    // `YEAR` is a preprocessor macro defined when compiling the source file.
    // For example:
    // $ g++ -D YEAR=\"2024\" HelloWorld.cpp
    // Which means that `YEAR` is replaced with `"2024"` during the compilation.
    //
    // Note that in C/C++, multiple string literals separated by whitespace are
    // concatenated into a single string literal.
    // For example:
    // "Hello, " "World!" is equivalent to "Hello, World!"
    //
    // Moreover say is that in `::std::cout`, the first `::` makes sure that 
    // the compiler searches for namespace `std` in the global namespace.
    // However, it can be omitted just like `std::endl`, because it is clear
    // that there is no nested namespace `std` defined in `shucxx2024`.
    // 
    // One more thing to say is that, `operator<<` is actually a function 
    // defined in the namespace `std`, which is overloaded for different types 
    // of arguments.
    // We don't need to write `std::operator<<` because the compiler will
    // automatically find the correct function in the namespace `std` based on
    // the rule of ADL (Argument-Dependent Lookup).
    ::std::cout << "SHU " YEAR ", Hello, World!" << std::endl;
}
}  // namespace shucxx2024