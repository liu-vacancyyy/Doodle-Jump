cmake_minimum_required(VERSION 3.10)
project(gameconfig)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
add_library(gameconfig config.cpp config.h)
target_link_libraries(gameconfig ${OpenCV_LIBS})