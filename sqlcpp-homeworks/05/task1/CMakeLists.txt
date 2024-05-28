cmake_minimum_required(VERSION 3.20)

set(PostgreSQL_ADDITIONAL_VERSION "16")

project(task1)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory("C:\\libpqxx-7.9.0" libpqxx-build)

add_executable(task1 src/main.cpp 
	src/db_connector.h
	src/db_connector.cpp)

target_link_libraries(task1 PRIVATE pqxx)