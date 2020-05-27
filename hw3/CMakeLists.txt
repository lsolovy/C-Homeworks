cmake_minimum_required(VERSION 3.15)
project(hw3)

configure_file(data.txt data.txt COPYONLY)

set(CMAKE_CXX_STANDARD 11)

add_executable(hw3 main.cpp Rectangle.cpp Rectangle.h)