cmake_minimum_required(VERSION 3.10)
project(AccentColor)


set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp  )

add_library(SO_CPP SHARED IMPORTED)
add_library(SO_ASM SHARED IMPORTED)


SET_PROPERTY(TARGET SO_CPP         PROPERTY IMPORTED_LOCATION ../../SO_CPP/cmake-build-debug/libSO_CPP.so)
SET_PROPERTY(TARGET SO_ASM         PROPERTY IMPORTED_LOCATION ../../SO_ASM.so)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR OFF)
set(CMAKE_PREFIX_PATH "PATH_TO_QT/QT_VERSION/QT_ARCH/lib/cmake")

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_executable(AccentColor main.cpp mainwindow.cpp mainwindow.h model.h model.cpp mainwindow.ui   )

target_link_libraries(AccentColor Qt5::Core)
target_link_libraries(AccentColor Qt5::Widgets)
target_link_libraries(AccentColor  SO_CPP)
target_link_libraries(AccentColor  SO_ASM)