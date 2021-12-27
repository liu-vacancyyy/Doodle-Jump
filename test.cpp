#include <opencv2/opencv.hpp>
#include <time.h>
#include "game_common/common.h"

using namespace std;

int main()
{
    uint64_t init_time=GetTimeNow();
    cv::VideoCapture cap(0);
    cv::Mat frame;
    while(1)
    {
        cap>>frame;
        std::cout<<uint64_t((GetTimeNow()-init_time))<<std::endl;
    }
}