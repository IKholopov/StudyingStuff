cmake_minimum_required(VERSION 2.8)
project(Stuff)

set(Stuff_SRCS main.cpp)
include_directories("${PROJECT_BINARY_DIR}")
include_directories(${CMAKE_SOURCE_DIR}/Graph/include)
add_executable(Stuff ${Stuff_SRCS})
target_link_libraries(Stuff Graph)

