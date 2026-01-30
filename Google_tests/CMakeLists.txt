project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_tests_run DynamicArrayTest.cpp)

target_link_libraries(Google_tests_run gtest gtest_main)
