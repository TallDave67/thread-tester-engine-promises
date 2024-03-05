cmake_minimum_required(VERSION 3.22.1)
project(thread-tester-engine-promises-src-core)

set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(
    ../comm
    ../util
)

add_library(thread-tester-engine-promises-src-core
    thread_driver.cpp
    thread_manager.cpp
    thread_wrapper.cpp
    thread_wrapper_promiseMatrixCalc.cpp
)

target_compile_options(thread-tester-engine-promises-src-core PRIVATE)
