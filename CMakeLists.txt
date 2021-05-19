cmake_minimum_required(VERSION 3.20.1)

set(this mbrowzer)

project(${this} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(external)
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)