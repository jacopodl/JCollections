cmake_minimum_required(VERSION 2.8)
project(LibJCollections)

set(SOURCE_FILES stack.c)
add_executable(SkTest ${SOURCE_FILES})

target_link_libraries(SkTest JCollections)
add_test(NAME stackTEST COMMAND SkTest)