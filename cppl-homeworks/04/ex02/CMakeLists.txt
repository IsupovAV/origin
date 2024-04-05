cmake_minimum_required(VERSION 3.14)

project(ex02)


# ищем библиотеку для подключения Catch2:
find_package(Catch2 CONFIG REQUIRED)

# добавляем запускаемый файл с именем проекта
add_executable(ex02 src/main.cpp
        src/test_case.cpp
        src/list.h)

# линкуем библиотеки Catch2
target_link_libraries(ex02 PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)
