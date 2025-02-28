cmake_minimum_required(VERSION 3.10)
project(task1) 

set(CMAKE_CXX_STANDARD 20)

#Добавление директории Catch2
add_subdirectory(./Catch2 Catch2-build)

#Установка переменной со списком исходников для тестового исполняемого файла
set (SOURCES_TEST_EXE test.cpp shape.cpp)	#transform.cpp
set (HEADERS_TEST_EXE shape.h)					#transform.h

#Создание исполняемого файла 
add_executable(task1 ${SOURCES_TEST_EXE} ${HEADERS_TEST_EXE})

#Линковка программы с библиотекой catch2
target_link_libraries(task1 PRIVATE Catch2::Catch2)