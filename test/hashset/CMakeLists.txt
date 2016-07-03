cmake_minimum_required(VERSION 2.8)
project(LibJCollections)

set(SOURCE_FILES hashset.c)
add_executable(HsTest ${SOURCE_FILES})

target_link_libraries(HsTest JCollections)
add_test(NAME hashsetTEST COMMAND HsTest)