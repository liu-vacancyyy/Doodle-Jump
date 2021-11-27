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

        int * pResults = NULL;
        
        pResults = facedetect_cnn(p_buffer_, (unsigned char*)(frame.ptr(0)), frame.cols, frame.rows, (int)frame.step);

        for(int i = 0; i < (pResults ? *pResults : 0); i++)
        {
            short * p = ((short*)(pResults+1))+142*i;
            int confidence = p[0];
            int x = p[1];
            int y = p[2];
            int w = p[3];
            int h = p[4];
            
            //show the score of the face. Its range is [0-100]
            char sScore[256];
            snprintf(sScore, 256, "%d", confidence);
            cv::putText(frame, sScore, cv::Point(x, y-3), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 1);
            //draw face rectangle
            cv::rectangle(frame, cv::Rect(x, y, w, h), cv::Scalar(0, 255, 0), 2);
            tl_=cv::Point2f(x,y);
            br_=cv::Point2f(w,h);
        }
    }
}