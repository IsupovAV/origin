cmake_minimum_required(VERSION 3.22)
project(task2)

set(CMAKE_CXX_STANDARD 20)

add_executable(task2 src/task2.cpp
        src/figure.cpp
        src/figure.h
        src/triangle.cpp
        src/triangle.h
        src/right_triangle.cpp
        src/right_triangle.h
        src/isosceles_triangle.cpp
        src/isosceles_triangle.h
        src/equilateral_triangle.cpp
        src/equilateral_triangle.h
        src/quadrangle.cpp
        src/quadrangle.h
        src/parallelogram.cpp
        src/parallelogram.h
        src/rectangle.cpp
        src/rectangle.h
        src/rhombus.cpp
        src/rhombus.h
        src/square.cpp
        src/square.h)
