cmake_minimum_required(VERSION 3.16)

project(task1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Concurrent Charts)



set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)


add_executable(task1
    ${PROJECT_SOURCES}
    graphic.h graphic.cpp graphic.ui

)


target_link_libraries(task1 Qt6::Widgets
                                Qt6::Concurrent
                                Qt6::Charts
                                )


