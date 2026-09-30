cmake_minimum_required(VERSION 3.31)
project(DynamicArray)

set(CMAKE_CXX_STANDARD 20)

add_executable(DynamicArray src/main.cpp)
target_include_directories(DynamicArray PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

enable_testing()
add_subdirectory(tests)
