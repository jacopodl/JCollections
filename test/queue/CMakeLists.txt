cmake_minimum_required(VERSION 2.8)
project(LibJCollections)
include(CTest)

set(SOURCE_FILES queue.c)
add_executable(QuTest ${SOURCE_FILES})

target_link_libraries(QuTest JCollections)
add_test(NAME queueTEST COMMAND QuTest)