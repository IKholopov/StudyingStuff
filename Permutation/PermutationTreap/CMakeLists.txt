project(PermutationTreap)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src ${PROJECT_NAME}_SRCS)
file(GLOB_RECURSE ${PROJECT_NAME}_HEADERS include/*.h*)
set(${PROJECT_NAME}_SRCS ${${PROJECT_NAME}_SRCS} ${${PROJECT_NAME}_HEADERS})
include_directories(${CMAKE_SOURCE_DIR}/ImplicitTreap/ImplicitTreap/include)
add_library(PermutationTreap ${${PROJECT_NAME}_SRCS})
target_link_libraries(PermutationTreap ImplicitTreap)
set_target_properties(PermutationTreap PROPERTIES LINKER_LANGUAGE CXX)
INCLUDE_DIRECTORIES(include)
