cmake_minimum_required(VERSION 3.10)
project(gameplay)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
add_library(gameplay fsm.cpp fsm.h)
target_link_libraries(gameplay 
                                            ${OpenCV_LIBS} 
                                            libsfml-graphics.so 
                                            libsfml-window.so
                                            libsfml-system.so)