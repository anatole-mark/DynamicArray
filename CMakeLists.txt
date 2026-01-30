cmake_minimum_required(VERSION 3.31)
project(DynamicArray)

set(CMAKE_CXX_STANDARD 20)

add_executable(DynamicArray main.cpp
        lab2.h)

add_subdirectory(Google_tests)
