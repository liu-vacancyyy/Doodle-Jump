cmake_minimum_required(VERSION 3.10)
 
project(vrgame) 

find_package(OpenCV 4  REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS} )
link_directories(${OpenCV_LIBRARY_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/game_common)
add_subdirectory(game_common)

include_directories(${PROJECT_SOURCE_DIR}/game_detector)
add_subdirectory(game_detector)

include_directories(${PROJECT_SOURCE_DIR}/game_resolver)
add_subdirectory(game_resolver)

include_directories(${PROJECT_SOURCE_DIR}/game_camera)
add_subdirectory(game_camera)

add_executable(vrgame 
    main.cpp)
target_link_libraries(vrgame 
    ${OpenCV_LIBS} 
    gamecamera
    gameconfig
    gamecommon
    gamefacedetectcnn
    gameresolver
    pthread 
    -lpthread -lm)