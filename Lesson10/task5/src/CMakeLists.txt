cmake_minimum_required(VERSION 3.22)
project(geometry)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../bin)
set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(geometry_src 
	geometry/figure.h 
	geometry/figure.cpp
	geometry/triangle.h 
	geometry/triangle.cpp
	geometry/right_triangle.h 
	geometry/right_triangle.cpp
	geometry/equilateral_triangle.h 
	geometry/equilateral_triangle.cpp
	geometry/isosceles_triangle.h 
	geometry/isosceles_triangle.cpp
	geometry/quadrangle.h 
	geometry/quadrangle.cpp
	geometry/parallelogram.h 
	geometry/parallelogram.cpp
	geometry/rectangle.h 
	geometry/rectangle.cpp
	geometry/rhombus.h 
	geometry/rhombus.cpp
	geometry/square.h 
	geometry/square.cpp
	)
	
add_library(geometry SHARED ${geometry_src})
