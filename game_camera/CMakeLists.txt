cmake_minimum_required(VERSION 3.10)

project(gamecamera)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
add_library(gamecamera camera.cpp camera.h)
target_link_libraries(gamecamera ${OpenCV_LIBS})