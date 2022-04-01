cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_COMPILER "clang++-11")
project(AlgGeneration LANGUAGES CXX)

SET(CMAKE_CXX_FLAGS "-Weverything -pedantic -Werror")

add_subdirectory (src)
