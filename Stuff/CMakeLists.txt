cmake_minimum_required(VERSION 2.8)
project(Stuff)

FIND_PACKAGE( Boost 1.50 COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_NAME}_SRCS)
file(GLOB_RECURSE ${PROJECT_NAME}_HEADERS include/*.h*)
set(${PROJECT_NAME}_SRCS ${${PROJECT_NAME}_SRCS} ${${PROJECT_NAME}_HEADERS})
include_directories("${PROJECT_BINARY_DIR}")
include_directories(${CMAKE_SOURCE_DIR}/Graph/include)
add_executable(Stuff ${${PROJECT_NAME}_SRCS})

target_link_libraries(Stuff Graph ${Boost_LIBRARIES})

