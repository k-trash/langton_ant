cmake_minimum_required(VERSION 3.16.3)
project(langton_ant CXX)

set(CMAKE_CXX_FLAGS "-lpng")

include_directories(
	include
)

add_library(ant_lib SHARED
	src/ant_lib.cpp
)

add_executable(ant_main src/ant_main.cpp)

target_link_libraries(ant_main
	ant_lib
	png
)
