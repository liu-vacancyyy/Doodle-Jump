#ifndef GAME_RESOLVER_H
#define GAME_RESOLVER_H
#include "../game_detector/facedetectcnn.h"
#include <opencv2/opencv.hpp>

#define DETECT_BUFFER_SIZE 0x20000

namespace gameresolver{
    class GameResolver
    {
    public:
        GameResolver();
        ~GameResolver();
        void GetRoi(cv::Mat frame);
    private:
        cv::Point2f tl_;
        cv::Point2f br_;
        unsigned char * p_buffer_;
    };
}
#endif