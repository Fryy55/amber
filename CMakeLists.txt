cmake_minimum_required(VERSION 3.31)
project(amber VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(${PROJECT_NAME} STATIC ${SOURCES})

set(INCLUDE "${PROJECT_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${INCLUDE}
        ${INCLUDE}/prelude
    PRIVATE
        ${INCLUDE}/amber/actions
        ${INCLUDE}/amber/settingsV3
        ${INCLUDE}/amber/utils
)


if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

if (PROJECT_IS_TOP_LEVEL)
    add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE GEODE_MOD_ID="_amber")

target_link_libraries(${PROJECT_NAME} geode-sdk)