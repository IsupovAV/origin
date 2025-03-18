cmake_minimum_required(VERSION 3.20)

project(task1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 REQUIRED COMPONENTS Widgets Core)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ExampleRace.cpp
        ExampleRace.h
)


qt_add_executable(task1
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(task1 PRIVATE Qt6::Widgets
                                            Qt6::Core)

qt_finalize_executable(task1)

