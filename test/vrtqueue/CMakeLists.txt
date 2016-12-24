cmake_minimum_required(VERSION 2.8)
project(LibJCollections)

set(SOURCE_FILES vrtqueue.c)
add_executable(VRTQTest ${SOURCE_FILES})

target_link_libraries(VRTQTest JCollections)
add_test(NAME vrtqueueTEST COMMAND VRTQTest)