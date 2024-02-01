cmake_minimum_required(VERSION 3.22)
project(leaver)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../bin)
set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(lib_src 
	leaver/leaver.h 
	leaver/leaver.cpp)

add_library(leaver SHARED ${lib_src})
