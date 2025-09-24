cmake_minimum_required(VERSION 3.10)
project(tw-assets C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

file(GLOB SRC_FILES
    "${CMAKE_SOURCE_DIR}/src/*.c"
)

add_executable(tw-assets ${SRC_FILES})

target_include_directories(tw-assets
    PRIVATE ${CMAKE_SOURCE_DIR}/src
    PUBLIC  ${CMAKE_SOURCE_DIR}/include
)
