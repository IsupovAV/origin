cmake_minimum_required(VERSION 3.20)
project(unit_tests)

set(CMAKE_CXX_STANDARD 20)

# ищем библиотеку для подключения Catch2:
find_package(Catch2 CONFIG REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../bin)

add_executable(unit_tests tests.cpp
        ../src/simple_unique_ptr.h
        )

# линкуем библиотеки Catch2
target_link_libraries(unit_tests PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)
