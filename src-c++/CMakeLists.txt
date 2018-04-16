cmake_minimum_required(VERSION 3.9)
project(blockchain_exp)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(cpr)
include_directories(${CPR_INCLUDE_DIRS})

add_executable(blockchain_exp main.cpp Blockchain.cpp Blockchain.hpp json.hpp picosha2.h crow_all.h)

target_link_libraries(blockchain_exp ${CPR_LIBRARIES} -lboost_system)