#cmake_minimum_required(VERSION 3.15)
cmake_minimum_required(VERSION 3.5)
project(generator)

set(CMAKE_CXX_STANDARD 14)

add_executable(generator main.cpp Model-Generator/model-generator.h Model-Generator/model-generator.cpp)