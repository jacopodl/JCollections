cmake_minimum_required(VERSION 2.8)
project(LibJCollections)

set(SOURCE_FILES lktest.c)
add_executable(LkTest ${SOURCE_FILES})

target_link_libraries(LkTest JCollections)
add_test(NAME LkListTEST COMMAND LkTest)