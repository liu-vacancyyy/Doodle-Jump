#include "config.h"

namespace gameconfig{
    DetectionConfig::DetectionConfig(){
        detection_read_.open("../config/detection.yaml",cv::FileStorage::READ);
        detection_read_["camera_id"]>>camera_id_;
        detection_read_["debug"]>>debug_;
        detection_read_.release();
    }
}