cmake_minimum_required(VERSION 3.22)
project(greet)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../../lib)

set(lib_src greet_lib/greeter.h greet_lib/greeter.cpp)
add_library(greet STATIC ${lib_src})
