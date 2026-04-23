cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if ("${CMAKE_SYSTEM_NAME}" STREQUAL "iOS" OR IOS)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
else()
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
endif()
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(amber VERSION 2.0.0)
# Local bindings repo
#set(GEODE_BINDINGS_REPO_PATH $ENV{GEODE_BINDINGS})

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}
)

message(STATUS "Defining `AMBER_EXPORTING`")
target_compile_definitions(${PROJECT_NAME} PRIVATE AMBER_EXPORTING)


if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

setup_geode_mod(${PROJECT_NAME})


if (DEFINED FRYY_LOCAL)
    message(STATUS "Adding tests")

    add_subdirectory(${PROJECT_SOURCE_DIR}/test ${CMAKE_CURRENT_BINARY_DIR}/amber-test)
endif()