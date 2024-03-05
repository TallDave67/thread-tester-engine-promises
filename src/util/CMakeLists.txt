cmake_minimum_required(VERSION 3.22.1)
project(thread-tester-engine-promises-src-util)

set(CMAKE_VERBOSE_MAKEFILE ON)

add_library(thread-tester-engine-promises-src-util
    timer.cpp
)

target_compile_options(thread-tester-engine-promises-src-util PRIVATE)
