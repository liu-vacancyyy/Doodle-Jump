#include "resolver.h"

namespace gameresolver{
    GameResolver::GameResolver(){
        p_buffer_ = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
        if(!p_buffer_)
        {
            fprintf(stderr, "Can not alloc buffer.\n");
        }
        tl_=cv::Point2f(-1,-1);
        br_=cv::Point2f(-1,-1);
    }

    GameResolver::~GameResolver(){
        free(p_buffer_);
    }

    void GameResolver::GetRoi(cv::Mat frame){

        int * p_results = NULL;
        int max_confidence=0;
        
        p_results = facedetect_cnn(p_buffer_, (unsigned char*)(frame.ptr(0)), frame.cols, frame.rows, (int)frame.step);

        for(int i = 0; i < (p_results ? *p_results : 0); i++)
        {
            short * p = ((short*)(p_results+1))+142*i;
            int confidence = p[0];
            int x = p[1];
            int y = p[2];
            int w = p[3];
            int h = p[4];
            if(confidence>max_confidence){
                cv::rectangle(frame, cv::Rect(x, y, w, h), cv::Scalar(0, 255, 0), 2);
                tl_=cv::Point2f(x,y);
                br_=cv::Point2f(w,h);
                max_confidence=confidence;
            }
        }

        if(tl_.x!=-1&&br_.x!=-1){
            if(!current_roi_.empty()){
                last_roi_=current_roi_.clone();
            }
            cv::Rect roi_rect(tl_,br_);
            current_roi_=frame(roi_rect);
        }
    }
}