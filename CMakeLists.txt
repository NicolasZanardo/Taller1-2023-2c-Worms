#===============================================================================
cmake_minimum_required(VERSION 3.22.0)
project(tp_worms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -pedantic-errors")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

#===============================================================================
add_subdirectory(client)
add_subdirectory(common_base)
add_subdirectory(server)
