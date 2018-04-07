cmake_minimum_required(VERSION 3.9)
project(src_c__)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(cpr)
add_executable(src_c__ main.cpp Blockchain.cpp Blockchain.hpp json.hpp picosha2.h)