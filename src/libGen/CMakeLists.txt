cmake_minimum_required(VERSION 3.20)
include(../cmake/init.cmake)
project(libGeneration VERSION 0.0)

# Enumerate every folder containing sources
file(GLOB base base/*.cpp)

# Create library
add_library(generation ${base})

target_include_directories(generation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
