cmake_minimum_required (VERSION 3.6)
project (sokohard)

set(CMAKE_CXX_FLAGS "-Wall -O3 -std=c++17 -stdlib=libc++")
set(CMAKE_CXX_COMPILER "clang++")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/out")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/out")

add_subdirectory ("${PROJECT_SOURCE_DIR}/src")
