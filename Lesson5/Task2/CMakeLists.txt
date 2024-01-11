cmake_minimum_required(VERSION 3.22)
project(task2)

set(CMAKE_CXX_STANDARD 20)

add_executable(task2 task2.cpp
        counter.cpp
        counter.h
        tester.cpp
        tester.h)
