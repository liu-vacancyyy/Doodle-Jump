#include "camera.h"

namespace gamecamera{
    GameCamera::GameCamera(gameconfig::DetectionConfig detection_config){
        cap_=new::cv::VideoCapture(detection_config.GetCameraId());
        if(!cap_->isOpened()){
            running_=false;
        }else{
            running_=true;
        }
        cap_->set(cv::CAP_PROP_FRAME_WIDTH,detection_config.GetWidth());
        cap_->set(cv::CAP_PROP_FRAME_HEIGHT,detection_config.GetHeight());
        init_time_=GetTimeNow();
        now_time_=GetTimeNow()-init_time_;
    }

    void GameCamera::GetImage(cv::Mat &frame){
        cap_->read(frame);
        now_time_=GetTimeNow()-init_time_;
    }
}