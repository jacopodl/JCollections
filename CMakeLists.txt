cmake_minimum_required(VERSION 2.8)
project(LibJCollections)

set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --pedantic")

set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
set(DEFAULT_INSTALL_PATH "${PROJECT_SOURCE_DIR}/bin")

include_directories(src)
add_subdirectory(src)
add_subdirectory(test)
