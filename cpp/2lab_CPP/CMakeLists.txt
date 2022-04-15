cmake_minimum_required(VERSION 3.20)
project(TritSet)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include/gtest)

add_executable(TritSet trit.h trit.cpp gtest_test.cpp)

target_link_libraries(TritSet gtest gtest_main)

set(CMAKE_CXX_STANDARD 11)


