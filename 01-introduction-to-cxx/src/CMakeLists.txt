set(TARGET_NAME ${PROJECT_NAME})
log_info("Target: ${TARGET_NAME}")

# TARGET_SRCS <- All files ending with ".cpp" in "src/"
file(GLOB_RECURSE TARGET_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Create the target with the given name and source files
add_executable(${TARGET_NAME} ${TARGET_SRCS})

# Include the "include/" directory
target_include_directories(${TARGET_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")

# Define the "YEAR" preprocessor macro
target_compile_definitions(${TARGET_NAME} PRIVATE "YEAR=\"2024\"")

