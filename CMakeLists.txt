cmake_minimum_required(VERSION 3.30)

project("SHUCXX2024")

set(SHUCXX2024_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include(${SHUCXX2024_PROJECT_DIR}/cmake/Logging.cmake)
include(${SHUCXX2024_PROJECT_DIR}/cmake/Compiler.cmake)

add_subdirectory("02-basic-cmake-example")
add_subdirectory("03-build-and-link-against-libraries")
add_subdirectory("05-concept-crtp")
add_subdirectory("06-exception-safety")
# MSVC does not support OpenMP properly!
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_subdirectory("07-openmp")
endif()

add_subdirectory("${SHUCXX2024_PROJECT_DIR}/externals/Yutils")