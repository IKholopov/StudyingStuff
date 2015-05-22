cmake_minimum_required(VERSION 2.8)
project(GraphUnitTests)
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(GraphUnitTests_SRCS ${PROJECT_SOURCE_DIR}/main.cpp ${PROJECT_INCLUDE_DIR}/TestShortestPath.hpp
${PROJECT_INCLUDE_DIR}/TestMST.h ${PROJECT_SOURCE_DIR}/TestMST.cpp )
include_directories("${PROJECT_BINARY_DIR}")
include_directories(${CMAKE_SOURCE_DIR}/Graph/include)
add_executable(GrpahUnitTests ${GraphUnitTests_SRCS})
target_link_libraries(GrpahUnitTests Graph)
include_directories("${PROJECT_INCLUDE_DIR}")
