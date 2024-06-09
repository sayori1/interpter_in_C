cmake_minimum_required(VERSION 3.16)
project(mari C)

set(CMAKE_C_STANDARD 11)


include_directories(src)
add_executable(mari src/main.c)
