cmake_minimum_required(VERSION 3.10)
project(hw3 C)

set(CMAKE_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -pedantic-errors -Werror ")

add_executable(hw3 main.c map_mtm.c)