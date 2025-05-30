cmake_minimum_required(VERSION 3.20)

project(
  qt_coursework
  VERSION 0.1
  LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(
  Qt6
  COMPONENTS Widgets Sql Concurrent Charts
  REQUIRED)

set(PROJECT_SOURCES main.cpp mainwindow.cpp mainwindow.h mainwindow.ui)

qt_add_executable(
  qt_coursework
  MANUAL_FINALIZATION
  ${PROJECT_SOURCES}
  utility.h
  database.h
  database.cpp
  setdbconnection.ui
  setdbconnection.h
  setdbconnection.cpp
  resource.qrc
  statistics.h
  statistics.cpp
  statistics.ui
  about.h about.cpp about.ui)

target_link_directories(${PROJECT_NAME} PUBLIC
                        ${CMAKE_CURRENT_SOURCE_DIR}/PG_Libs
						)
target_link_libraries(
  qt_coursework
  PRIVATE Qt6::Widgets
          Qt6::Concurrent
          Qt6::Sql
          Qt6::Charts
          libcrypto-3-x64
          libiconv-2
          libintl-9
          libpq
          libssl-3-x64
		  )

qt_finalize_executable(qt_coursework)
