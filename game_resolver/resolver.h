#ifndef GAME_RESOLVER_H
#define GAME_RESOLVER_H
#include "../third_party/game_detector/facedetectcnn.h"
#include "../game_common/common.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <thread>
#include <mutex>
#include <math.h>

namespace gameresolver{

    class GameResolver
    {
    public:
         /**************************************************************************
         * @name            GameResolver
         * @brief           构造GameResolver
         *
         ***************************************************************************/
        GameResolver();

         /**************************************************************************
         * @name            ~GameResolver
         * @brief           析构GameResolver
         *
         ***************************************************************************/
        ~GameResolver();

         /**************************************************************************
         * @name            GetRoi
         * @brief           获取当前帧的感兴趣区域(人脸区域)并更新
         *
         * @param           [in] frame   当前帧
         * @param           [in] current_time   当前时间
         ***************************************************************************/
        void GetRoi(cv::Mat frame,float current_time);

        /**************************************************************************
         * @name            SetControl
         * @brief           设置游戏控制参数
         * 
         ***************************************************************************/
        void SetControl();

    private:
        /**************************************************************************
         * @name            FindFeatureMatch
         * @brief           寻找前后帧相匹配的特征点
         *
         ***************************************************************************/
        void FindFeatureMatch();

        /**************************************************************************
         * @name            ResolvePose
         * @brief           解算头部位姿
         *
         ***************************************************************************/
        void ResolvePose();

        /**************************************************************************
         * @name            SmoothAngle
         * @brief           平滑处理yaw轴旋转角度
         *
         * @return           yaw轴旋转角度 
         ***************************************************************************/
        float SmoothAngle();

        /*************************数据寄存器*************************/
        bool have_face_; //这一帧是否检测到人脸
        std::mutex locker_; //改变游戏控制参数需要使用的互斥锁
        std::deque<MatchFrame> rois_; //roi区域的历史信息，目前只存两帧
        std::vector<cv::KeyPoint> last_key_points_; //上一帧的特征点
        std::vector<cv::KeyPoint> current_key_points_; //当前帧的特征点
        std::vector<cv::DMatch> orb_matches_; //前后帧特征点的匹配关系
        cv::Mat R_; //解算得到的头部旋转矩阵
        cv::Mat t_; //解算得到的头部平移矩阵

        /*************************数据处理器*************************/
        unsigned char * p_buffer_; //人脸检测模型
        cv::Ptr<cv::FeatureDetector> orb_detector_; //orb检测器
        cv::Ptr<cv::DescriptorExtractor> orb_descriptor_; //orb描述器
        cv::Ptr<cv::DescriptorMatcher> orb_matcher_; //orb匹配器
        cv::KalmanFilter yaw_filter_; //卡尔曼滤波器

        /*************************常用参数*************************/
        const unsigned int detect_buffer_size_=0x20000; //模型参数,切勿修改
        const int max_size_=2; //最大历史信息数量
        const int max_time_diff_=1000000000; //两帧最大允许时间差
        cv::Point2f principal_point_; //相机光心
        float focal_length_; //相机焦距
        cv::Mat K_; //相机内参
    };
}
#endif