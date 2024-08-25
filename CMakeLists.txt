cmake_minimum_required(VERSION 3.30)

project("SHUCXX2024")

include(${CMAKE_SOURCE_DIR}/cmake/Logging.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/Compiler.cmake)

add_subdirectory("01-introduction-to-cxx")
add_subdirectory("02-basic-cmake-example")
add_subdirectory("03-build-and-link-against-libraries")