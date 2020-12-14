cmake_minimum_required(VERSION 3.15)

project(fzbz VERSION 0 LANGUAGES CXX)

find_package(range-v3 REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(fizzbuzz-range main.cpp)
target_link_libraries(fizzbuzz-range PRIVATE range-v3)
