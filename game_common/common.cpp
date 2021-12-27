#include "common.h"

bool gameClose=false;
GameControl gameControl;
GameConfig gameConfig;
DetectionConfig detectionConfig;

DetectionConfig::DetectionConfig(){
    detection_read_.open("../config/detection.yaml",cv::FileStorage::READ);
    if(!detection_read_.isOpened()){
        std::cout<<"open detection yaml failed!"<<std::endl;
    }
    detection_read_["video"]>>video_;
    if(video_)
        detection_read_["video_path"]>>video_path_;
    if(picture_){
        detection_read_["picture1_path"]>>picture1_path_;
        detection_read_["picture2_path"]>>picture2_path_;
    }
    detection_read_["picture"]>>picture_;
    detection_read_["k_mat"]>>k_mat_;
    detection_read_["dist_coffes"]>>
    detection_read_["camera_id"]>>camera_id_;
    detection_read_["debug"]>>debug_;
    detection_read_["width"]>>width_;
    detection_read_["height"]>>height_;
    detection_read_["focal_length"]>>focal_length_;
    detection_read_["resolve"]>>resolve_;
    detection_read_["record"]>>record_;
    detection_read_.release();
}

GameConfig::GameConfig(){
    game_read_.open("../config/game.yaml",cv::FileStorage::READ);
    if(!game_read_.isOpened()){
        std::cout<<"open game yaml failed!"<<std::endl;
    }
    game_read_["debug"]>>debug_;
    game_read_["mode"]>>mode_;
    game_read_["test_state"]>>test_state_;
    game_read_["fps"]>>fps_;
    game_read_.release();
}

uint64_t GetTimeNow(){
    struct timeval tv; 
    gettimeofday(&tv, nullptr);
    return (tv.tv_sec * 1e6 + tv.tv_usec); 
}