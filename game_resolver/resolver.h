#ifndef GAME_RESOLVER_H
#define GAME_RESOLVER_H
#include "../game_detector/facedetectcnn.h"
#include "../game_common/tool.h"
#include <opencv2/opencv.hpp>

#define DETECT_BUFFER_SIZE 0x20000

namespace gameresolver{
    class GameResolver
    {
    public:
        GameResolver();
        ~GameResolver();
        void GetRoi(cv::Mat frame);
        void SetControl(GameControl &game_control);
    private:
        cv::Point2f tl_;
        cv::Point2f br_;
        unsigned char * p_buffer_;
        cv::Mat last_roi_;
        cv::Mat current_roi_;
    };
}
#endif