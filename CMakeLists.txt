cmake_minimum_required(VERSION 3.22.1)
project(thread-tester-engine-promises)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_subdirectory(src)
include_directories(
        src
        src/comm
        src/core
        src/util
)

add_executable(thread-tester-engine-promises main.cpp)

target_link_libraries(thread-tester-engine-promises thread-tester-engine-promises-src)
