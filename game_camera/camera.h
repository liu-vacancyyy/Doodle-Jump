#ifndef GAME_CAMERA_H
#define GAME_CAMERA_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include "../game_common/tool.h"
#include "../game_config/config.h"

namespace gamecamera{
    class GameCamera
    {
    public:
        GameCamera(gameconfig::DetectionConfig detection_config);
        void GetImage(cv::Mat &frame);
        uint64_t GetFrameTime(){return now_time_;}
        bool GetRunning(){return running_;}
    private:
        uint64_t init_time_;
        uint64_t now_time_;
        cv::VideoCapture *cap_;
        bool running_;
    };
}

#endif