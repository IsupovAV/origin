cmake_minimum_required(VERSION 3.20)

project(task2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Concurrent Charts PrintSupport)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)


add_executable(task2
    ${PROJECT_SOURCES}
    graphic.h graphic.cpp graphic.ui

)

add_compile_definitions(QCUSTOMPLOT_USE_LIBRARY)
target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(task2 Qt6::Widgets
                                      Qt6::Concurrent
                                      Qt6::Charts
                                      Qt6::PrintSupport
                                      qcustomplot2.dll
                                      )
                           

