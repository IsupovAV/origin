cmake_minimum_required(VERSION 3.22)
project(task1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

include_directories(src/greet_lib)

add_executable(task1 src/main.cpp)
add_subdirectory(src)
target_link_libraries(task1 greet)

