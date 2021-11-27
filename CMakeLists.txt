cmake_minimum_required(VERSION 3.10)
 
project(vrgame) 

find_package(OpenCV 4  REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS} )
link_directories(${OpenCV_LIBRARY_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/game_common)
add_subdirectory(game_common)

include_directories(${PROJECT_SOURCE_DIR}/game_camera)
add_subdirectory(game_camera)

include_directories(${PROJECT_SOURCE_DIR}/game_config)
add_subdirectory(game_config)

add_executable(vrgame 
    main.cpp)
target_link_libraries(vrgame 
    ${OpenCV_LIBS} 
    gamecamera
    gameconfig
    gamecommon
    pthread 
    -lpthread -lm)