cmake_minimum_required(VERSION 3.9)
project(src_c__)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(cpr)
include_directories(${CPR_INCLUDE_DIRS})

add_executable(src_c__ main.cpp Blockchain.cpp Blockchain.hpp json.hpp picosha2.h)

target_link_libraries(src_c__ ${CPR_LIBRARIES})