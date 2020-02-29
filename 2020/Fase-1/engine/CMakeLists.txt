cmake_minimum_required(VERSION 3.15)
project(engine)

set(CMAKE_CXX_STANDARD 14)

include_directories(tinyxml2)

add_executable(engine
        Model-Read-Tests/box_div_1.3d
        tinyxml2/tinyxml2.cpp
        tinyxml2/tinyxml2.h
        XML-Examples/ex-config-1.xml
        main.cpp)
