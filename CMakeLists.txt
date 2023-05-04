cmake_minimum_required(VERSION 3.20)
PROJECT(UCO)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BUILD_TYPE Debug)
include_directories(uco)
add_executable(example example.cpp)

target_link_libraries(example PRIVATE uco)




add_subdirectory(uco)




