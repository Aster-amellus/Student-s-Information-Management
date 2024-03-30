cmake_minimum_required(VERSION 3.27)
project(StuInfo C)

set(CMAKE_C_STANDARD 11)

add_executable(StuInfo main.c
        funcs.h
        funcs.c
)
