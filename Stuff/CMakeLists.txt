cmake_minimum_required(VERSION 2.8)
project(Stuff)

FIND_PACKAGE( Boost 1.50 COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

set(Stuff_SRCS main.cpp)
include_directories("${PROJECT_BINARY_DIR}")
include_directories(${CMAKE_SOURCE_DIR}/Graph/include)
add_executable(Stuff ${Stuff_SRCS})

target_link_libraries(Stuff Graph ${Boost_LIBRARIES})

