cmake_minimum_required(VERSION 3.10)

project(gameresolver)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
add_library(gameresolver resolver.cpp resolver.h)
target_link_libraries(gameresolver ${OpenCV_LIBS} gamefacedetectcnn)