set(TARGET_NAME ${PROJECT_NAME})
shucxx2024_log_info("${SHUCXX2024_LOG_CAT} Target <exe>: ${TARGET_NAME}")

# Find OpenMP
find_package(OpenMP REQUIRED)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 23)

function(add_openmp_executable TARGET_NAME TARGET_SRCS)
    add_executable(${TARGET_NAME} ${TARGET_SRCS})
    target_link_libraries(${TARGET_NAME} PUBLIC OpenMP::OpenMP_CXX)
    target_compile_options(${TARGET_NAME} PRIVATE -fopenmp)
endfunction()

# For each .cpp file in the current directory, add an executable with the same name
file(GLOB_RECURSE TARGET_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
foreach(TARGET_SRC ${TARGET_SRCS})
    get_filename_component(TARGET_NAME ${TARGET_SRC} NAME_WE)
    add_openmp_executable(${TARGET_NAME} ${TARGET_SRC})
endforeach(TARGET_SRC ${TARGET_SRCS})


