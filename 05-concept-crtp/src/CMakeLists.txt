# TARGET_NAME "06-concept-crtp"
set(TARGET_NAME ${PROJECT_NAME})
shucxx2024_log_info("${SHUCXX2024_LOG_CAT} Target <exe>: ${TARGET_NAME}")

# TARGET_SRCS files are all the source files in the src/
file(GLOB_RECURSE TARGET_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(${TARGET_NAME} ${TARGET_SRCS})
target_include_directories(${TARGET_NAME}
                           PRIVATE "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(
    ${TARGET_NAME} PRIVATE 
    Yutils::Yutils
)