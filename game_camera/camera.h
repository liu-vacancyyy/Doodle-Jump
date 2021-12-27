#ifndef GAME_CAMERA_H
#define GAME_CAMERA_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include "../game_common/common.h"
#include <thread>
#include <mutex>

namespace gamecamera{
    class GameCamera
    {
    public:
        GameCamera();
        GameCamera(DetectionConfig detection_config);
        void TakeFrame();
        bool GetImage(cv::Mat &frame,uint64_t &camera_time);
        inline uint64_t GetCameraTime() {return camera_time_;}
        inline bool GetRunning() {return cap_->isOpened();}
    private:
        uint64_t init_time_;
        uint64_t camera_time_=0;
        uint64_t last_camera_time_=0;
        cv::VideoCapture *cap_;
        std::thread camera_thread_;
        cv::Mat camera_frame_;
        std::mutex camera_locker_;
    };
}

#endif