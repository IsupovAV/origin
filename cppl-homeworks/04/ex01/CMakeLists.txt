cmake_minimum_required(VERSION 3.14)

project(ex01)


# ищем библиотеку для подключения Catch2:
find_package(Catch2 CONFIG REQUIRED)

# добавляем запускаемый файл с именем проекта
add_executable(ex01 main.cpp)

# линкуем библиотеки Catch2
target_link_libraries(ex01 PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)
