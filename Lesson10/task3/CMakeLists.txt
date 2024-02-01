cmake_minimum_required(VERSION 3.22)
project(client_dll)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

include_directories(src/leaver)

add_executable(client_dll src/main.cpp)
add_subdirectory(src)
target_link_libraries(client_dll leaver)

