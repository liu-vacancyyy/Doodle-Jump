#include "camera.h"

namespace gamecamera{
    GameCamera::GameCamera(){
    }

    GameCamera::GameCamera(DetectionConfig detection_config){
        cap_=new::cv::VideoCapture(detection_config.GetCameraId());
        cap_->set(cv::CAP_PROP_FRAME_WIDTH,detection_config.GetWidth());
        cap_->set(cv::CAP_PROP_FRAME_HEIGHT,detection_config.GetHeight());
        init_time_=GetTimeNow();
        camera_thread_=std::thread(&GameCamera::TakeFrame,this);
        camera_thread_.detach();
    }

    void GameCamera::TakeFrame(){
        while(cap_->isOpened()){
            cap_->read(camera_frame_);
            camera_time_=GetTimeNow()-init_time_;
            if(detectionConfig.GetDebug())
                std::cout<<"camera_time="<<uint64_t(camera_time_)<<std::endl;
        }
    }

    bool GameCamera::GetImage(cv::Mat &frame,uint64_t &camera_time){
        if(camera_time_!=last_camera_time_){
            camera_locker_.lock();
                frame=camera_frame_.clone();
                camera_time=camera_time_;
                last_camera_time_=camera_time_;
            camera_locker_.unlock();
            return true;
        }else{
            return false;
        }
    }
}