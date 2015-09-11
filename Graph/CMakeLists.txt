cmake_minimum_required(VERSION 2.8)
project(Graph)
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)


aux_source_directory(${PROJECT_SOURCE_DIR} Graph_SRCS)
file(GLOB_RECURSE Graph_HEADERS "${PROJECT_INCLUDE_DIR}/*.h")
MESSAGE("${Graph_HEADERS}")
include_directories(${PROJECT_INCLUDE_DIR})
#[[set(Graph_SRCS ${PROJECT_INCLUDE_DIR}/IGraph.h
${PROJECT_INCLUDE_DIR}/UnorientedGraph.h
${PROJECT_INCLUDE_DIR}/Graph.h ${PROJECT_INCLUDE_DIR}/GraphManager.h
${PROJECT_INCLUDE_DIR}/GraphFileFormat.h ${PROJECT_INCLUDE_DIR}/ValuedEdge.hpp
${PROJECT_INCLUDE_DIR}/MinDSU.h
${PROJECT_INCLUDE_DIR}/GraphValuedEdge.hpp  ${PROJECT_INCLUDE_DIR}/MinPQ.hpp
${PROJECT_INCLUDE_DIR}/CustomGenerator.h
${PROJECT_INCLUDE_DIR}/Kruskal.h ${PROJECT_INCLUDE_DIR}/Prim.h ${PROJECT_INCLUDE_DIR}/Boruvka.h
${PROJECT_SOURCE_DIR}/Graph.cpp ${PROJECT_SOURCE_DIR}/UnorientedGraph.cpp ${PROJECT_SOURCE_DIR}/GraphManager.cpp
${PROJECT_SOURCE_DIR}/MinDSU.cpp
${PROJECT_SOURCE_DIR}/CustomGenerator.cpp
${PROJECT_SOURCE_DIR}/Kruskal.cpp ${PROJECT_SOURCE_DIR}/Prim.cpp ${PROJECT_SOURCE_DIR}/Boruvka.cpp) ]]
include_directories("${PROJECT_BINARY_DIR}")
set(Graph_SRCS ${Graph_SRCS} ${Graph_HEADERS})
add_library(Graph ${Graph_SRCS} ${Graph_HEADERS})
