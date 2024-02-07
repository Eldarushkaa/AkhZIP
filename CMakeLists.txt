set (CMAKE_CXX_STANDARD 11)
cmake_minimum_required(VERSION 3.10.0)
project(Akh)

add_executable(${PROJECT_NAME} main.cpp libraries/libsais.c algorithems.cpp)
