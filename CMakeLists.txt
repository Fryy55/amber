cmake_minimum_required(VERSION 3.31)
project(amber VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Local bindings repo
#set(GEODE_BINDINGS_REPO_PATH $ENV{GEODE_BINDINGS})

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

if (PROJECT_IS_TOP_LEVEL)
    add_library(${PROJECT_NAME} SHARED ${SOURCES})
else()
    add_library(${PROJECT_NAME} STATIC ${SOURCES})
endif()

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)


if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

if (PROJECT_IS_TOP_LEVEL)
    add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

    setup_geode_mod(${PROJECT_NAME})
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE GEODE_MOD_ID="_amber")

    target_link_libraries(${PROJECT_NAME} geode-sdk)
endif()