cmake_minimum_required(VERSION 3.14)
project(ex03)

set(CMAKE_CXX_STANDARD 20)

# ищем библиотеку для подключения Catch2:
find_package(Catch2 CONFIG REQUIRED)

add_executable(ex03 src/main.cpp
        src/simple_vector.h
        src/test_case.cpp)

# линкуем библиотеки Catch2
target_link_libraries(ex03 PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)
