cmake_minimum_required(VERSION 3.22)
project(Task2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Task2 task2.cpp
        geometric_exception.h
        geometric_exception.cpp
        figure.cpp
        figure.h
        triangle.cpp
        triangle.h
        right_triangle.cpp
        right_triangle.h
        isosceles_triangle.cpp
        isosceles_triangle.h
        equilateral_triangle.cpp
        equilateral_triangle.h
        quadrangle.cpp
        quadrangle.h
        parallelogram.cpp
        parallelogram.h
        rectangle.cpp
        rectangle.h
        rhombus.cpp
        rhombus.h
        square.cpp
        square.h)
