cmake_minimum_required(VERSION 3.22)
project(my_first_cmake_project)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
add_executable(my_first_cmake_project main.cpp)
