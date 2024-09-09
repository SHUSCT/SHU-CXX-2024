project("03-build-and-link-against-libraries" VERSION 1.0.0)

if(NOT DEFINED SPDLOG_HOME)
    log_fatal("SPDLOG_HOME is not set")
else()
    shucxx2024_log_info("SPDLOG_HOME: ${SPDLOG_HOME}")
    find_package(spdlog REQUIRED PATHS ${SPDLOG_HOME})
endif()

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/test")
add_subdirectory("${SHUCXX2024_PROJECT_DIR}/externals/Yutils" "${CMAKE_BINARY_DIR}/externals/Yutils")