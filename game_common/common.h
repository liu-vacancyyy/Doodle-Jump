#ifndef GAME_TOOL_H
#define GAME_TOOL_H

#include <sys/time.h>
#include <opencv2/opencv.hpp>
#include <iostream>

bool gameOver=false; //游戏结束标志位

struct MatchFrame{
    cv::Mat frame; //图像
    cv::Point2f tl; //感兴趣区域左上顶点
    cv::Point2f br; //感兴趣区域右下顶点
    float time; //取帧时间
}; //需要匹配的帧

struct GameControl{
    int direction=0; //方向
    int speed=0; //速度
}gameControl; //游戏控制参数

class GameConfig
{
public:
    GameConfig();
private:
    cv::FileStorage game_read_;
    int difficulty_;
}gameConfig;

class DetectionConfig
{
public:
    DetectionConfig();
    int GetCameraId() {return camera_id_;}
    bool GetDebug() {return debug_;}
    int GetWidth() {return width_;}
    int GetHeight() {return height_;}
    cv::Mat GetKMat() {return k_mat_;}
    float GetFocalLength() {return focal_length_;}
private:
    cv::FileStorage detection_read_;
    cv::Mat k_mat_;
    int camera_id_;
    int debug_;
    int width_;
    int height_;
    float focal_length_;
}detectionConfig;

/**************************************************************************
 * @name            GetTimeNow
 * @brief           获取当前时间
 *
 ***************************************************************************/
uint64_t GetTimeNow();

#endif