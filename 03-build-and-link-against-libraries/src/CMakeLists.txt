include(${SHUCXX2024_PROJECT_DIR}/cmake/InstallLib.cmake)

# Build Math library ============================================================

set(TARGET_NAME "${PROJECT_NAME}-Math")
shucxx2024_log_info("${SHUCXX2024_LOG_CAT} Target: ${TARGET_NAME}")

add_library(${TARGET_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/Math.cpp")
add_library(shucxx2024::${TARGET_NAME} ALIAS ${TARGET_NAME})

target_include_directories(
    ${TARGET_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(BUILD_SHARED_LIBS)
    shucxx2024_log_info("Building a shared library")
    target_compile_definitions(${TARGET_NAME} PRIVATE SHUCXX2024_EXPORT)
    target_compile_definitions(${TARGET_NAME} INTERFACE SHUCXX2024_IMPORT)
else()
    shucxx2024_log_info("Building a static library")
endif()

install_libraries(shucxx2024Math shucxx2024 ${TARGET_NAME})

# Build TimeCounter library ====================================================

set(TARGET_NAME "${PROJECT_NAME}-TimeCounter")
shucxx2024_log_info("${SHUCXX2024_LOG_CAT} Target <lib>: ${TARGET_NAME}")

add_library(${TARGET_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/TimeCounter.cpp")
add_library(shucxx2024::${TARGET_NAME} ALIAS ${TARGET_NAME})

target_include_directories(
    ${TARGET_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(BUILD_SHARED_LIBS)
    shucxx2024_log_info("Building a shared library")
    target_compile_definitions(${TARGET_NAME} PRIVATE SHUCXX2024_EXPORT)
    target_compile_definitions(${TARGET_NAME} INTERFACE SHUCXX2024_IMPORT)
else()
    shucxx2024_log_info("Building a static library")
endif()

include(${SHUCXX2024_PROJECT_DIR}/cmake/InstallLib.cmake)
install_libraries(shucxx2024Utilities shucxx2024 ${TARGET_NAME})

# Build Logger library ============================================================

set(TARGET_NAME "${PROJECT_NAME}-Logger")
shucxx2024_log_info("${SHUCXX2024_LOG_CAT} Target: ${TARGET_NAME}")

add_library(${TARGET_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/Logger.cpp")
add_library(shucxx2024::${TARGET_NAME} ALIAS ${TARGET_NAME})

target_include_directories(
    ${TARGET_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(BUILD_SHARED_LIBS)
    shucxx2024_log_info("Building a shared library")
    target_compile_definitions(${TARGET_NAME} PRIVATE SHUCXX2024_EXPORT)
    target_compile_definitions(${TARGET_NAME} INTERFACE SHUCXX2024_IMPORT)
else()
    shucxx2024_log_info("Building a static library")
endif()

target_link_libraries(${TARGET_NAME} PUBLIC 
                      spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)

include(${SHUCXX2024_PROJECT_DIR}/cmake/InstallLib.cmake)

install_libraries(shucxx2024Utilities shucxx2024 ${TARGET_NAME})