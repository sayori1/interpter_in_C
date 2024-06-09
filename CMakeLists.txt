cmake_minimum_required(VERSION 3.16)
project(mari C)

set(CMAKE_C_STANDARD 11)


file(GLOB_RECURSE SOURCES "src/*.c")

include_directories(src)

add_executable(mari ${SOURCES})