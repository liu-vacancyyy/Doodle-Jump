#ifndef GAME_TOOL_H
#define GAME_TOOL_H

#include <sys/time.h>
#include <opencv2/opencv.hpp>
#include <iostream>

bool gameOver=false;

struct GameControl{
    int direction=0;
    int speed=0;
}gameControl;

uint64_t GetTimeNow();

#endif