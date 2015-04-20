cmake_minimum_required(VERSION 2.8)
project(PageRank)
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(PageRank_SRCS ${PROJECT_INCLUDE_DIR}/PageRank.hpp
${PROJECT_SOURCE_DIR}/main.cpp ${PROJECT_SOURCE_DIR}/PageRank.cpp)
include_directories("${PROJECT_BINARY_DIR}")
include_directories(${CMAKE_SOURCE_DIR}/Graph/include)
add_executable(PageRank ${PageRank_SRCS})
target_link_libraries(PageRank Graph)
include_directories("${PROJECT_INCLUDE_DIR}")
