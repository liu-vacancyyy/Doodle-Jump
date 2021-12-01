#include "resolver.h"

namespace gameresolver{
    GameResolver::GameResolver(){
        p_buffer_ = (unsigned char *)malloc(detect_buffer_size_);
        if(!p_buffer_)
        {
            fprintf(stderr, "Can not alloc buffer.\n");
        }
        orb_detector_=cv::ORB::create();
        orb_descriptor_=cv::ORB::create();
        orb_matcher_=cv::DescriptorMatcher::create("BruteForce-Hamming");
        K_=detectionConfig.GetKMat();
        principal_point_.x=detectionConfig.GetWidth()/2;
        principal_point_.y=detectionConfig.GetHeight()/2;
        focal_length_=detectionConfig.GetFocalLength();
    }

    GameResolver::~GameResolver(){
        free(p_buffer_);
    }

    void GameResolver::GetRoi(cv::Mat frame,float current_time){

        int * p_results = NULL;
        int max_confidence=0;
        
        cv::Point2f tl=cv::Point2f(-1,-1);
        cv::Point2f br=cv::Point2f(-1,-1);
            
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
                tl=cv::Point2f(x,y);
                br=cv::Point2f(w,h);
                max_confidence=confidence;
            }
        }

        if(tl.x!=-1&&br.x!=-1){
            have_face_=true;
            MatchFrame match_frame;
            cv::Rect roi_rect(tl,br);
            match_frame.frame=frame(roi_rect);
            match_frame.tl=tl;
            match_frame.br=br;
            match_frame.time=current_time;
            rois_.push_back(match_frame);
            if(rois_.size()>max_size_){
                rois_.pop_front();
            }
        }else{
            have_face_=false;
        }
    }

    void GameResolver::SetControl(){
        float smooth_yaw=0;
        if(have_face_&&rois_.size()>1){
            if(rois_.back().time-rois_.front().time<max_time_diff_){
                FindFeatureMatch();
                ResolvePose();
                smooth_yaw=SmoothAngle();
            }
        }
        locker_.lock();
        if(smooth_yaw==0){
            gameControl.direction=0;
            gameControl.speed=0;
        }else{
            if(smooth_yaw>0)
                gameControl.direction=1;
            if(smooth_yaw<0)
                gameControl.direction=-1;
            gameControl.speed=1;
        }
        locker_.unlock();
    }

    void GameResolver::FindFeatureMatch(){
        if(rois_.back().time-rois_.front().time<max_time_diff_){
            cv::Mat last_descriptors;
            cv::Mat current_descriptors;
            orb_detector_->detect(rois_.front().frame,last_key_points_);
            orb_detector_->detect(rois_.front().frame,current_key_points_);
            orb_descriptor_->compute(rois_.front().frame,last_key_points_,last_descriptors);
            orb_descriptor_->compute(rois_.back().frame,current_key_points_,current_descriptors);
            orb_matcher_->match(last_descriptors,current_descriptors,orb_matches_);
        }
    }

    void GameResolver::ResolvePose(){
        std::vector<cv::Point2f> last_points;
        std::vector<cv::Point2f> current_points;
        for(int i=0;i<(int)orb_matches_.size();i++){
            last_points.push_back(last_key_points_[orb_matches_[i].queryIdx].pt+rois_.front().tl);
            current_points.push_back(current_key_points_[orb_matches_[i].trainIdx].pt+rois_.back().tl);
        }

        cv::Mat essential_matrix;
        essential_matrix = cv::findEssentialMat(last_points,current_points,focal_length_,principal_point_);
        cv::recoverPose(essential_matrix,last_points,current_points,R_,t_,focal_length_,principal_point_);
        if(detectionConfig.GetDebug()){
            std::cout<<"essential_matrix is "<<std::endl<< essential_matrix<<std::endl;
            std::cout<<"R is"<<std::endl<<R_<<std::endl;
            std::cout<<"t is"<<std::endl<<t_<<std::endl;
        }
    }

    float GameResolver::SmoothAngle(){
        cv::Mat origin_vector = (cv::Mat_<float> (3,1) << 1,0,0);
        origin_vector.convertTo(origin_vector,CV_32F);
        R_.convertTo(R_,CV_32F);
        cv::Mat changed_vector=R_*origin_vector;

        if(detectionConfig.GetDebug()){
            std::cout<<"changed vector"<<std::endl<<changed_vector<<std::endl;
        }

        if(changed_vector.at<float>(0)<0){
            return 0;
        }else{
            if(changed_vector.at<float>(1)>0){
                return acos(1/sqrt(pow(changed_vector.at<float>(0),2)+pow(changed_vector.at<float>(1),2)));
            }else{
                return -acos(1/sqrt(pow(changed_vector.at<float>(0),2)+pow(changed_vector.at<float>(1),2)));
            }
        }
    }
}