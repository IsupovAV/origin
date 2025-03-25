cmake_minimum_required(VERSION 3.20)

project(task1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Concurrent Sql)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        database.h
        database.cpp



)

add_executable(task1
	${PROJECT_SOURCES}
        setdbconnection.ui
        setdbconnection.h
        setdbconnection.cpp
        resource.qrc

)


target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/PG_Libs)
target_link_libraries(task1 PRIVATE Qt6::Widgets
											Qt6::Concurrent
											Qt6::Sql
                                             libcrypto-3-x64
                                             libiconv-2
                                             libintl-9
                                             libpq
                                             libssl-3-x64)


