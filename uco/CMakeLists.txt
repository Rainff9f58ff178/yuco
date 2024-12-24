cmake_minimum_required(VERSION 3.20)
PROJECT(UCO)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BUILD_TYPE Debug)
set(SRCS 
    Scheduler.cpp
    AsyncScheduler.cpp) 
include_directories(${CMAKE_SOURCE_DIR}/uco)

add_library(uco STATIC ${SRCS})
target_link_libraries(uco uring)





