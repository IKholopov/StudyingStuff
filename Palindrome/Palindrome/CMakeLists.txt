cmake_minimum_required(VERSION 2.8)
project(Palindrome)
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/ImplicitTreap/ImplicitTreap/include)

set(Palindrome_SRCS ${PROJECT_INCLUDE_DIR}/Palindrome.h ${PROJECT_INCLUDE_DIR}/PalindromeTreap.h
${PROJECT_SOURCE_DIR}/Palindrome.cpp ${PROJECT_SOURCE_DIR}/PalindromeTreap.cpp)
include_directories("${PROJECT_BINARY_DIR}")
add_library(Palindrome ${Palindrome_SRCS})
SET_TARGET_PROPERTIES(Palindrome PROPERTIES LINKER_LANGUAGE CXX)
include_directories("${PROJECT_INCLUDE_DIR}")
