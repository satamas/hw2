cmake_minimum_required(VERSION 2.8.4)
project(hw2)

set(SOURCE_FILES main.cpp Polygon.cpp)
add_definitions(-std=gnu++0x)
add_executable(hw2 ${SOURCE_FILES})