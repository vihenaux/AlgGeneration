cmake_minimum_required(VERSION 3.20)
include(../cmake/init.cmake)
project(libGeneration VERSION 0.0)

# Create libtest

file(GLOB sources libtest/*.cpp libtest/*.hpp)
add_library(test ${sources})

target_include_directories(test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# libGen base test executable

add_executable(test-libgen-base base/test-libgen-base.cpp base/testclasses.cpp)

target_link_libraries(test-libgen-base LINK_PUBLIC test generation)

install(TARGETS test-libgen-base RUNTIME DESTINATION Release/bin)
