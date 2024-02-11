cmake_minimum_required(VERSION 3.22)
project(race_simulator)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

include_directories(src/race_objects)

add_executable(race_simulator 
	src/race_driver.cpp 
	src/simulator/simulator.h
	src/simulator/simulator.cpp
	)

add_subdirectory(src)
target_link_libraries(race_simulator race_objects)

