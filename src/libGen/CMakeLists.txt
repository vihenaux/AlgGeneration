cmake_minimum_required(VERSION 3.20)
include(../cmake/init.cmake)
project(libAlgGen VERSION 0.0)


####################
# Generation Utils #
####################

# Enumerate every source file
file(GLOB utils alggen/utils/*.cpp alggen/utils/*.hpp)

# Create library
add_library(AlgGenUtils ${utils})

target_include_directories(AlgGenUtils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


###################
# Generation Base #
###################

# Enumerate every source file
file(GLOB base alggen/base/*.cpp alggen/base/*.hpp)

# Create library
add_library(AlgGenBase ${base})

target_include_directories(AlgGenBase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


###########################
# Generation Neighborhood #
###########################

# Enumerate every source file
file(GLOB neighborhood alggen/neighborhood/*.cpp alggen/neighborhood/*.hpp)

# Create library
add_library(AlgGenNeighborhood ${neighborhood})

target_link_libraries(AlgGenNeighborhood LINK_PUBLIC AlgGenBase)

target_include_directories(AlgGenNeighborhood PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


#######################
# Generation Solution #
#######################

# Enumerate every source file
file(GLOB solution alggen/solution/*.cpp alggen/solution/*.hpp)

# Create library
add_library(AlgGenSolution ${solution})

target_link_libraries(AlgGenSolution LINK_PUBLIC AlgGenBase AlgGenNeighborhood AlgGenProblem AlgGenUtils)

target_include_directories(AlgGenSolution PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


###############################
# Generation Search Algorithm #
###############################

# Enumerate every source file
file(GLOB searchalgorithm alggen/searchalgorithm/*.cpp alggen/searchalgorithm/*.hpp)

# Create library
add_library(AlgGenSearchAlgorithm ${searchalgorithm})

target_link_libraries(AlgGenSearchAlgorithm LINK_PUBLIC AlgGenBase)

target_include_directories(AlgGenSearchAlgorithm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


######################
# Generation Problem #
######################

# Enumerate every source file
file(GLOB problem alggen/problem/*.cpp alggen/problem/*.hpp)

# Create library
add_library(AlgGenProblem ${problem})

target_link_libraries(AlgGenProblem LINK_PUBLIC AlgGenBase AlgGenNeighborhood AlgGenSolution)

target_include_directories(AlgGenProblem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


########################
# Generation Selection #
########################

# Enumerate every source file
file(GLOB selection alggen/selection/*.cpp alggen/selection/*.hpp)

# Create library
add_library(AlgGenSelection ${selection})

target_link_libraries(AlgGenSelection LINK_PUBLIC AlgGenBase)

target_include_directories(AlgGenSelection PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
