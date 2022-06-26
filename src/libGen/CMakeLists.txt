cmake_minimum_required(VERSION 3.20)
include(../cmake/init.cmake)
project(libGeneration VERSION 0.0)


###################
# Generation Base #
###################

# Enumerate every source file
file(GLOB base alggen/base/*.cpp alggen/base/*.hpp)

# Create library
add_library(GenerationBase ${base})

target_include_directories(GenerationBase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


###########################
# Generation Neighborhood #
###########################

# Enumerate every source file
file(GLOB neighborhood alggen/neighborhood/*.cpp alggen/neighborhood/*.hpp)

# Create library
add_library(GenerationNeighborhood ${neighborhood})

target_link_libraries(GenerationNeighborhood LINK_PUBLIC GenerationBase)

target_include_directories(GenerationNeighborhood PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


#######################
# Generation Solution #
#######################

# Enumerate every source file
file(GLOB solution alggen/solution/*.cpp alggen/solution/*.hpp)

# Create library
add_library(GenerationSolution ${solution})

target_link_libraries(GenerationSolution LINK_PUBLIC GenerationBase GenerationNeighborhood)

target_include_directories(GenerationSolution PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
