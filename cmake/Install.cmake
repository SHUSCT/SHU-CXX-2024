include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# ==============================================================================
# @breif Install target libraries
# @note
#   1. ${PROJECT_NAME} is defined outside the function.
#   2. ${LIB NAMES} can be multiple lib targets.
function(shucxx2024_install_libraries LIB_NAMESPACE LIB_NAMES)
    # Install libraries
    install(
        TARGETS ${LIB_NAMES}
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION Lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
    )

    # Install headers
    install(
        DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION include
    )

    # Install cmake config files
    install(
        EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${LIB_NAMESPACE}::
        DESTINATION lib/cmake/${PROJECT_NAME}
    )

    # Generate and install version file
    write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
    )

    # Generate and install config file
    configure_package_config_file(
        ${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
    )

    # Install config files
    install(
        FILES
            ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
            ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION 
            lib/cmake/${PROJECT_NAME}
    )
endfunction()
