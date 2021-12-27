#ifndef GAME_COMMON_H
#define GAME_COMMON_H

#include <sys/time.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>

extern bool gameClose; //游戏关闭标志位

enum GAMESTATE{
    START=0,READY,JUMP,OVER,TEST
}; //游戏状态，START:开始界面，READY：准备界面，UP:人物向上，DOWN:人物向下，OVER：结束界面

enum PLATCOLOR{
    GREEN=0,WHITE,BLUE,BREAK
}; //跳板颜色，GREEN：普通跳板，WHITE：一次性跳板，BLUE：移动跳板，BREAK：损坏跳板

enum GAMEMODE{
    KEYBOARD=0,FACE,DOUBLE
}; //游戏模式，KEYBOARD:键盘控制，FACE:头部控制，DOUBLE:双重控制

struct MatchFrame{
    cv::Mat frame; //图像
    cv::Point2f tl; //感兴趣区域左上顶点
    cv::Point2f br; //感兴趣区域右下顶点
    float time; //取帧时间
}; //需要匹配的帧

struct GameControl{
    int direction=0; //方向
    int speed=0; //速度
}; //游戏控制参数
extern GameControl gameControl;

class GameConfig
{
public:
    GameConfig();
    inline int GetDebug() {return debug_;}
    inline int GetMode() {return mode_;}
    inline int GetTestState() {return test_state_;}
    inline float GetFPS() {return fps_;}
private:
    cv::FileStorage game_read_;
    int debug_;
    int mode_;
    int test_state_;
    float fps_;
};
extern GameConfig gameConfig;

class DetectionConfig
{
public:
    DetectionConfig();
    inline int GetCameraId() {return camera_id_;}
    inline bool GetDebug() {return debug_;}
    inline int GetWidth() {return width_;}
    inline int GetHeight() {return height_;}
    inline cv::Mat GetKMat() {return k_mat_;}
    inline cv::Mat GetDistCoffes() {return dist_coffes_;}
    inline float GetFocalLength() {return focal_length_;}
    inline bool GetVideo() {return video_;}
    inline bool GetPicture() {return picture_;}
    inline std::string GetVideoPath() {return video_path_;}
    inline std::string GetPicture1Path() {return picture1_path_;}
    inline std::string GetPicture2Path() {return picture2_path_;}
    inline bool GetResolve() {return resolve_;}
    inline bool GetRecord() {return record_;}
private:
    cv::FileStorage detection_read_; 
    cv::Mat k_mat_;
    cv::Mat dist_coffes_;
    int camera_id_;
    bool debug_;
    int width_;
    int height_;
    float focal_length_;
    bool video_;
    bool picture_;
    std::string video_path_;
    std::string picture1_path_;
    std::string picture2_path_;
    bool resolve_;
    bool record_;
};
extern DetectionConfig detectionConfig;

struct GamePlat{
    PLATCOLOR color; //跳板颜色
    int x; //跳板在游戏窗口x坐标
    int y; //跳板在游戏窗口y坐标
    bool on; //该跳板是否显示
}; //游戏跳板

/**************************************************************************
 * @name            GetTimeNow
 * @brief           获取当前时间
 ***************************************************************************/
uint64_t GetTimeNow();

#endif