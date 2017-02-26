cmake_minimum_required(VERSION 3.6)
project(fdf)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES main.c)
add_executable(fdf ${SOURCE_FILES})