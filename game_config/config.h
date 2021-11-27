#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include <opencv2/opencv.hpp>
#include <string>

namespace gameconfig{
    class GameConfig
    {
    public:
        GameConfig();
        ~GameConfig();
    private:
        cv::FileStorage game_read_;
        int difficulty_;
    };

    class DetectionConfig
    {
    public:
        DetectionConfig();
        ~DetectionConfig();
        int GetCameraId(){return camera_id_;}
        bool GetDebug(){return debug_;}
    private:
        cv::FileStorage detection_read_;
        int camera_id_;
        int debug_;
    };
}
#endif