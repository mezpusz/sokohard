cmake_minimum_required (VERSION 3.6)
project (sokohard)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -stdlib=libc++")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_COMPILER "clang++")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/out")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/out")

add_subdirectory ("${PROJECT_SOURCE_DIR}/src")
