cmake_minimum_required(VERSION 2.8)
project(Graph)
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(Graph_SRCS ${PROJECT_INCLUDE_DIR}/Graph.h ${PROJECT_INCLUDE_DIR}/GraphManager.h
${PROJECT_INCLUDE_DIR}/GraphFileFormat.h ${PROJECT_INCLUDE_DIR}/ValuedEdge.hpp
${PROJECT_INCLUDE_DIR}/GraphIntValuedEdge.h ${PROJECT_INCLUDE_DIR}/GraphDoubleValuedEdge.h ${PROJECT_INCLUDE_DIR}/MinPQ.hpp
${PROJECT_SOURCE_DIR}/Graph.cpp ${PROJECT_SOURCE_DIR}/GraphManager.cpp ${PROJECT_SOURCE_DIR}/GraphIntValuedEdge.cpp ${PROJECT_SOURCE_DIR}/GraphDoubleValuedEdge.cpp)
include_directories("${PROJECT_BINARY_DIR}")
add_library(Graph ${Graph_SRCS})
include_directories("${PROJECT_INCLUDE_DIR}")
