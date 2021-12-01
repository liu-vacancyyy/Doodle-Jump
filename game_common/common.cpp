#include "common.h"

DetectionConfig::DetectionConfig(){
    detection_read_.open("../config/detection.yaml",cv::FileStorage::READ);
    detection_read_["k_mat"]>>k_mat_;
    detection_read_["camera_id"]>>camera_id_;
    detection_read_["debug"]>>debug_;
    detection_read_["width"]>>width_;
    detection_read_["height"]>>height_;
    detection_read_["focal_length"]>>focal_length_;
    detection_read_.release();
}

uint64_t GetTimeNow(){
    struct timeval tv; 
    gettimeofday(&tv, nullptr);
    return (tv.tv_sec * 1e6 + tv.tv_usec); 
}