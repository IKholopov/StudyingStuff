cmake_minimum_required(VERSION 2.8)
project(KthOrderStatistcis)
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(KthOrderStatistics_SRCS ${PROJECT_SOURCE_DIR}/PSTree.cpp
${PROJECT_INCLUDE_DIR}/PSTree.h)
include_directories("${PROJECT_BINARY_DIR}")
include_directories(${CMAKE_SOURCE_DIR}/PersistentData/include)
add_library(KthOrderStatistics ${KthOrderStatistics_SRCS})
target_link_libraries(KthOrderStatistics PersistentData)
include_directories("${PROJECT_INCLUDE_DIR}")
