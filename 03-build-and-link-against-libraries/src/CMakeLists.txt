set(TARGET_NAME ${PROJECT_NAME})
log_info("Building target: ${TARGET_NAME}")

file(GLOB_RECURSE TARGET_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
log_info("Found source files: ${TARGET_SRCS}")

add_library(${TARGET_NAME} ${TARGET_SRCS})
add_library(shucxx2024::${TARGET_NAME} ALIAS ${TARGET_NAME})

target_include_directories(
    ${TARGET_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(BUILD_SHARED_LIBS)
    log_info("Building a shared library")
    target_compile_definitions(${TARGET_NAME} PRIVATE SHUCXX2024_EXPORT)
    target_compile_definitions(${TARGET_NAME} INTERFACE SHUCXX2024_IMPORT)
else()
    log_info("Building a static library")
endif()

# find_package(spdlog REQUIRED PATHS ${SPDLOG_HOME})
# target_link_libraries(${TARGET_NAME} PUBLIC spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)${PROJECT_NAME}