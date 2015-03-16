cmake_minimum_required(VERSION 2.8)
project(KthOrderStatistcis)
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(KthOrderStatistics_SRCS ${PROJECT_SOURCE_DIR}/main.cpp)
include_directories("${PROJECT_BINARY_DIR}")
add_executable(KthOrderStatistics ${KthOrderStatistics_SRCS})
include_directories("${PROJECT_INCLUDE_DIR}")
