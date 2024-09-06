set(TARGET_NAME "${PROJECT_NAME}-test")
log_info("${LOG_CAT} Target <exe>: ${TARGET_NAME}")

# TARGET_SRCS <- All files ending with ".cpp" in "src/"
file(GLOB_RECURSE TARGET_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
log_info("Source Files: ${TARGET_SRCS}")

# Create the target with the given name and source files
add_executable(${TARGET_NAME} ${TARGET_SRCS})

target_link_libraries(
    ${TARGET_NAME} PRIVATE 
    shucxx2024::${PROJECT_NAME}-TimeCounter 
    shucxx2024::${PROJECT_NAME}-Math
    shucxx2024::${PROJECT_NAME}-Logger
)
