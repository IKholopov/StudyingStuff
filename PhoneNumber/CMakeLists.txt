cmake_minimum_required(VERSION 2.8)
project(PhoneNumber)
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src ${PROJECT_NAME}_SRCS)
file(GLOB_RECURSE ${PROJECT_NAME}_HEADERS include/*.h*)
set(${PROJECT_NAME}_SRCS ${${PROJECT_NAME}_SRCS} ${${PROJECT_NAME}_HEADERS})
include_directories("${PROJECT_BINARY_DIR}")
add_executable(PhoneNumber ${${PROJECT_NAME}_SRCS})
include_directories("${PROJECT_INCLUDE_DIR}")
