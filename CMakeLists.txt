cmake_minimum_required(VERSION 2.8.11)

project(scale)
add_library(scale STATIC scale.cpp)

include_directories(${CMAKE_SOURCE_DIR})
link_directories(${CMAKE_BINARY_DIR}/lib)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


enable_testing()
set(CMAKE_CTEST_COMMAND ctest -V)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})

macro(test_it thename)
	if ("${${thename}_sources}" STREQUAL "")
		set(${thename}_sources tests/${thename}.cpp)
	endif()
	add_executable(${thename} EXCLUDE_FROM_ALL ${${thename}_sources})
	target_link_libraries(${thename} scale)
	add_dependencies(check ${thename})
	add_test(NAME ${thename} COMMAND ${CMAKE_BINARY_DIR}/bin/${thename}${CMAKE_EXECUTABLE_SUFFIX})
endmacro()

test_it(test_8x8)
test_it(test_8x8s)
test_it(test_8x8s_small)
