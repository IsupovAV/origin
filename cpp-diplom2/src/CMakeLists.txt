cmake_minimum_required(VERSION 3.22)
project(race_objects)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../bin)
set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(race_objects_src 
	race_objects/boots.h 
	race_objects/boots.cpp
	race_objects/broom.h 
	race_objects/broom.cpp
	race_objects/camel.h 
	race_objects/camel.cpp
	race_objects/centaur.h 
	race_objects/centaur.cpp
	race_objects/constants.h 
	race_objects/eagle.h 
	race_objects/eagle.cpp
	race_objects/fast_camel.h 
	race_objects/fast_camel.cpp
	race_objects/flying_carpet.h 
	race_objects/flying_carpet.cpp
	race_objects/vehicle.h 
	race_objects/vehicle.cpp
	race_objects/vehicle_air.h 
	race_objects/vehicle_air.cpp
	race_objects/vehicle_land.h 
	race_objects/vehicle_land.cpp
	)
	
add_library(race_objects SHARED ${race_objects_src})
