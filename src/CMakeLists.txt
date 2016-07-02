cmake_minimum_required(VERSION 2.8)
project(LibJCollections)

add_library(JCollections lklist.c stack.c queue.c hashtable.c hashset.c utils.c)

file(GLOB HEADERS ${PUBLIC_SRC_HEADERS})
file(COPY ${HEADERS} DESTINATION "${INCLUDE_PATH}" PATTERN "jcollections.h" EXCLUDE)

configure_file("${PROJECT_SOURCE_DIR}/jcollections.h" "${INCLUDE_PATH}/jcollections.h")