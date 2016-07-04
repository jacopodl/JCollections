cmake_minimum_required(VERSION 2.8)
project(LibJCollections)
include(CTest)

set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)
set (VERSION_PATCH 0)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --pedantic --std=c99")

set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

set(PUBLIC_SRC_HEADERS "${PROJECT_SOURCE_DIR}/src/*.h")
set(INCLUDE_PATH "${PROJECT_SOURCE_DIR}/include")

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)
