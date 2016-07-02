cmake_minimum_required(VERSION 2.8)
project(LibJCollections)

set(SOURCE_FILES hashtable.c)
add_executable(HtTest ${SOURCE_FILES})

target_link_libraries(HtTest JCollections)
add_test(NAME hashtableTEST COMMAND HtTest)