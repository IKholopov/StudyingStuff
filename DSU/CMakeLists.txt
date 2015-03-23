cmake_minimum_required(VERSION 2.8)
project(DSU)
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(DSU_SRCS ${PROJECT_SOURCE_DIR}/main.cpp ${PROJECT_SOURCE_DIR}/DSU.cpp
${PROJECT_INCLUDE_DIR}/DSU.h)
include_directories("${PROJECT_BINARY_DIR}")
add_executable(DSU ${DSU_SRCS})
include_directories("${PROJECT_INCLUDE_DIR}")
