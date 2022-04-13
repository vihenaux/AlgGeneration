# Set clang as compiler

set(CMAKE_CXX_COMPILER "/usr/bin/clang++-11")

# Use C++ standard 20

set(CMAKE_CXX_STANDARD 20)

# Remove warnings in case of multiple calls to init.cmake

SET(CMAKE_CXX_FLAGS "")

# Add every clang warnings

include(${CMAKE_SOURCE_DIR}/cmake/functions.cmake)
ADD_COMPILER_FLAG("-Weverything")			# Option for Clang only. Activates every warning possible
ADD_COMPILER_FLAG("-pedantic")				# Use pedantic
ADD_COMPILER_FLAG("-Wno-c++98-compat")		# Remove c++98 compat warning because it is a bad one
ADD_COMPILER_FLAG("-Wno-padded")			# Padding is managed by the compiler, this warning is useless
ADD_COMPILER_FLAG("-Werror")				# Do not permit any warning

# Add optimization flags

ADD_COMPILER_FLAG("-O3")
