cmake_minimum_required(VERSION 2.8)
project(LibJCollections)

set(SOURCE_FILES vrtlist.c)
add_executable(VRTLTest ${SOURCE_FILES})

target_link_libraries(VRTLTest JCollections)
add_test(NAME vrtlistTEST COMMAND VRTLTest)