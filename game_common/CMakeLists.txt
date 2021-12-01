cmake_minimum_required(VERSION 3.10)
project(gamecommon)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
add_library(gamecommon common.cpp common.h)
target_link_libraries(gamecommon ${OpenCV_LIBS})