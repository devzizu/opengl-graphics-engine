#cmake_minimum_required(VERSION 3.15)
cmake_minimum_required(VERSION 3.5)
project(generator)

set(CMAKE_CXX_STANDARD 14)

add_executable(generator main.cpp Model-Generator/headers/model-generator.h Model-Generator/model-generator.cpp Model-Generator/model-info.cpp Model-Generator/headers/model-info.h Model-Generator/bezier-patch.cpp Model-Generator/headers/bezier-patch.h)