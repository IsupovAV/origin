cmake_minimum_required(VERSION 3.20)

project(ex02)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ex02 main.cpp 
	big_integer/big_integer.h
	big_integer/big_integer.cpp)