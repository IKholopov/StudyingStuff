cmake_minimum_required(VERSION 2.8)
project(HamiltonCircuits)
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(HamiltonCircuits_SRCS ${PROJECT_INCLUDE_DIR}/Hamilton.h
${PROJECT_SOURCE_DIR}/main.cpp ${PROJECT_SOURCE_DIR}/Hamilton.cpp)
include_directories("${PROJECT_BINARY_DIR}")
include_directories(${CMAKE_SOURCE_DIR}/Graph/include)
add_executable(HamiltonCircuits ${HamiltonCircuits_SRCS})
target_link_libraries(HamiltonCircuits Graph)
include_directories("${PROJECT_INCLUDE_DIR}")
