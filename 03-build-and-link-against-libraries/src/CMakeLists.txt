find_package(spdlog REQUIRED PATHS $ENV{SPDLOG_HOME})

# Build TimeCounter library ====================================================

set(TARGET_NAME "${PROJECT_NAME}-TimeCounter")
log_info("Target: ${TARGET_NAME}")

add_library(${TARGET_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/TimeCounter.cpp")
add_library(${GLOBAL_NAMESPACE}::${TARGET_NAME} ALIAS ${TARGET_NAME})

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

target_link_libraries(${TARGET_NAME} PUBLIC 
                      spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)

include(${CMAKE_SOURCE_DIR}/cmake/InstallLib.cmake)
install_libraries(${TARGET_NAME} ${GLOBAL_NAMESPACE} ${TARGET_NAME})

# Build Math library ============================================================

set(TARGET_NAME "${PROJECT_NAME}-Math")
log_info("Target: ${TARGET_NAME}")

add_library(${TARGET_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/Math.cpp")
add_library(${GLOBAL_NAMESPACE}::${TARGET_NAME} ALIAS ${TARGET_NAME})

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

target_link_libraries(${TARGET_NAME} PUBLIC 
                      spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)

include(${CMAKE_SOURCE_DIR}/cmake/InstallLib.cmake)

install_libraries(${TARGET_NAME} ${GLOBAL_NAMESPACE} ${TARGET_NAME})