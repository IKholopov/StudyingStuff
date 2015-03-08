cmake_minimum_required(VERSION 2.8)
project(ImplicitTreap)
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(ImplicitTreap_SRCS ${PROJECT_INCLUDE_DIR}/ImplicitTreapNode.h
${PROJECT_INCLUDE_DIR}/ImplicitTreapTree.h)
include_directories("${PROJECT_BINARY_DIR}")
add_library(ImplicitTreap ${ImplicitTreap_SRCS})
SET_TARGET_PROPERTIES(ImplicitTreap PROPERTIES LINKER_LANGUAGE CXX)
include_directories("${PROJECT_INCLUDE_DIR}")
set(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${PROJECT_INCLUDE_DIR})
