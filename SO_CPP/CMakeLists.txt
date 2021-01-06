cmake_minimum_required(VERSION 3.14)
project(SO_CPP)

set(CMAKE_CXX_STANDARD 17)

add_library(SO_CPP SHARED libraryCPP.cpp libraryCPP.h)
#add_executable(SO_CPP library.cpp library.h)