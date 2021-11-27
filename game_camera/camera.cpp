#include "camera.h"

using namespace gamecommon;

namespace gamecamera{
    GameCamera::GameCamera(int id){
        cap_=new::cv::VideoCapture(id);
        if(!cap_->isOpened()){
            running_=false;
        }else{
            running_=true;
        }
        init_time_=GetTimeNow();
        now_time_=GetTimeNow()-init_time_;
    }

    void GameCamera::GetImage(cv::Mat &frame){
        cap_->read(frame);
        now_time_=GetTimeNow()-init_time_;
    }
}