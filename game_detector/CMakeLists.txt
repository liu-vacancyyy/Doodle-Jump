# CMakeLists for libfacedetectcnn

project(libfacedetection)

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_definitions(-D_ENABLE_AVX2)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx2 -mfma")

include(CMakePackageConfigHelpers)
include(GenerateExportHeader)
include(GNUInstallDirs)

# Create a library
ADD_LIBRARY(gamefacedetectcnn 
                            facedetectcnn-data.cpp 
                            facedetectcnn.cpp 
                            facedetectcnn-model.cpp 
                            facedetectcnn.h
                            facedetection_export.h)