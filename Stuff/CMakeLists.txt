cmake_minimum_required(VERSION 2.8)
project(Stuff)

set(Stuff_SRCS main.cpp)
include_directories("${PROJECT_BINARY_DIR}")
add_executable(Stuff ${Stuff_SRCS})
