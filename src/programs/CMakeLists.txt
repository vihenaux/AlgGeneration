cmake_minimum_required(VERSION 3.20)
include(../cmake/init.cmake)
project(everyExe VERSION 0.0)

add_executable(test main.cpp)

target_link_libraries(test LINK_PUBLIC libTest)

install(TARGETS test RUNTIME DESTINATION Release/bin)
