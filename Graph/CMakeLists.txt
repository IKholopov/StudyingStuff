cmake_minimum_required(VERSION 2.8)
project(Graph)
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)


aux_source_directory(${PROJECT_SOURCE_DIR} ${PROJECT_NAME}_SRCS)
file(GLOB_RECURSE ${PROJECT_NAME}_HEADERS ${PROJECT_INCLUDE_DIR}/*.h*)
set(${PROJECT_NAME}_SRCS ${${PROJECT_NAME}_SRCS} ${${PROJECT_NAME}_HEADERS})
include_directories(${PROJECT_INCLUDE_DIR})
include_directories("${PROJECT_BINARY_DIR}")
add_library(Graph ${${PROJECT_NAME}_SRCS})
