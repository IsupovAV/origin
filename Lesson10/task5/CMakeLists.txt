cmake_minimum_required(VERSION 3.22)
project(task5)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

include_directories(src/geometry)

add_executable(task5 src/task5.cpp)
add_subdirectory(src)
target_link_libraries(task5 geometry)

