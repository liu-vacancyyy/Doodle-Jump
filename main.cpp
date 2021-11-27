#include "game_camera/camera.h"
#include <thread>
#include <signal.h>
#include "game_config/config.h"

bool gameOver=false;

void signalHandler(int signal){
    gameOver=true;
}

void GamePlaying(){
    while (!gameOver)
    {
    }
    std::cout<<"Game Over!"<<std::endl;
}

void DetectionRunning(){
    cv::Mat frame;
    gameconfig::DetectionConfig detectionConfig;
    gamecamera::GameCamera gameCamera(detectionConfig.GetCameraId());
    while (gameCamera.GetRunning()&&!gameOver)
    {
        gameCamera.GetImage(frame);
        if(detectionConfig.GetDebug()){
            cv::imshow("detection",frame);
            cv::waitKey(1);
        }
    }
    if(!gameCamera.GetRunning())
        std::cout<<"Get frame failed!"<<std::endl;
}

int main(){
    signal(SIGINT, signalHandler);
    std::thread gameThread(GamePlaying);
    std::thread detectionThread(DetectionRunning);
    gameThread.join();
    detectionThread.join();
    return 0;
}