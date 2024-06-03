cmake_minimum_required(VERSION 3.20)
include(../cmake/init.cmake)
project(libGeneration VERSION 0.0)

# Create libtest

file(GLOB sources libtest/*.cpp libtest/*.hpp)
add_library(test ${sources})

target_include_directories(test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# libGen base test executable

add_executable(test-libgen-base base/test-libgen-base.cpp base/testclasses.cpp)

target_link_libraries(test-libgen-base LINK_PUBLIC test AlgGenBase)

install(TARGETS test-libgen-base RUNTIME DESTINATION Release/bin)

# libGen solution test executable

add_executable(test-libgen-solution solution/test-libgen-solution.cpp)

target_link_libraries(test-libgen-solution LINK_PUBLIC test AlgGenSolution)

install(TARGETS test-libgen-solution RUNTIME DESTINATION Release/bin)

# libGen problem test executable

add_executable(test-libgen-problem problem/test-libgen-problem.cpp)

target_link_libraries(test-libgen-problem LINK_PUBLIC test AlgGenProblem)

install(TARGETS test-libgen-problem RUNTIME DESTINATION Release/bin)

# regtests executable

add_executable(test-regtests regtests/test-regtests.cpp)

target_link_libraries(test-regtests LINK_PUBLIC test AlgGenProblem AlgGenSearchAlgorithm)

install(TARGETS test-regtests RUNTIME DESTINATION Release/bin)

file(COPY regtests/test_files DESTINATION .)
