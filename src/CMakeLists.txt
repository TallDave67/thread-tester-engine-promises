cmake_minimum_required(VERSION 3.22.1)
project(thread-tester-engine-promises-src)

set(CMAKE_VERBOSE_MAKEFILE ON)

add_subdirectory(comm)
add_subdirectory(core)
add_subdirectory(util)
include_directories(
    comm
    core
    util
)

add_library(thread-tester-engine-promises-src
    src_main.cpp
)

target_compile_options(thread-tester-engine-promises-src PRIVATE)

target_link_libraries(thread-tester-engine-promises-src
        thread-tester-engine-promises-src-comm
        thread-tester-engine-promises-src-core
        thread-tester-engine-promises-src-util
)
