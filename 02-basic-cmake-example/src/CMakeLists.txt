# TARGET_NAME <- "02-basic-cmake-example"
set(TARGET_NAME ${PROJECT_NAME})
shucxx2024_log_info("${SHUCXX2024_LOG_CAT} Target <exe>: ${TARGET_NAME}")

# TARGET_SRCS <- All files ending with ".cpp" in "src/"
file(GLOB_RECURSE TARGET_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
shucxx2024_log_info("Source Files: ${TARGET_SRCS}")

# Create the target with the given name and source files
# Equivalent to: -o <target-name> <source-files>
add_executable(${TARGET_NAME} ${TARGET_SRCS})

# Include the "include/" directory
# Equivalent to: -I <include-directory>
target_include_directories(${TARGET_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")

# Define the "TARGET_NAME" preprocessor macro
# Equivalent to: -D TARGET_NAME="<target-name>"
target_compile_definitions(${TARGET_NAME} PRIVATE "TARGET_NAME=\"${TARGET_NAME}\"")
