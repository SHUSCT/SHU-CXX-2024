// #pragma once is a non-standard but widely supported preprocessor directive
// designed to cause the current source file to be included only once in a
// single compilation.
//
// Q: Why we need to make sure that a header file is included only once?
// A: If a header file is included multiple times in a single compilation unit,
//    the compiler will generate multiple definitions for the same functions,
//    classes, or variables, which will cause a linker error.
#pragma once

// Namespace: shucxx2024
// The functions and classes defined in a namespace can only be accessed using
// the scope resolution operator `::`.
namespace shucxx2024
{
// Function declaration for `sayHello`.
// A non-inline and non-template function should not be defined in a header
// file. If multiple source files include the header file, the function will be
// defined multiple times in each compilation unit, which will cause a linker
// error.
//
// It is a good practice to declare the function in a header file and define it
// in a source file.
void sayHello();
}  // namespace shucxx2024

// Note that `using namespace XXX;` is a bad practice in a header file because
// it will pollute the global namespace of the source file that includes the
// header file.
