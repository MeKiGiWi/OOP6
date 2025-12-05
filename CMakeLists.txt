cmake_minimum_required(VERSION 3.10)
project(DungeonEditor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()
include_directories(include)

find_package(GTest QUIET)
add_subdirectory(src)
add_subdirectory(tests)
