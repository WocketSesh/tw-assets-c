cmake_minimum_required(VERSION 3.10)
project(tw-assets VERSION 1.0.0 LANGUAGES C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

file(GLOB SRC_FILES
    "${CMAKE_SOURCE_DIR}/src/*.c"
)

add_library(tw-assets STATIC ${SRC_FILES})

include(GNUInstallDirs)

target_include_directories(tw-assets
    PRIVATE 
        ${CMAKE_SOURCE_DIR}/src
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    PUBLIC  
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(TARGETS tw-assets
    EXPORT tw-assetsTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT tw-assetsTargets
    FILE tw-assetsTargets.cmake
    NAMESPACE tw::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tw-assets
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/tw-assetsConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)


configure_package_config_file(
    "${CMAKE_SOURCE_DIR}/cmake/tw-assetsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/tw-assetsConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/tw-assets"
)


install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/tw-assetsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/tw-assetsConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tw-assets
)


