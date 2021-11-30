#include "game_camera/camera.h"
#include <thread>
#include <signal.h>
#include "game_config/config.h"
#include "game_resolver/resolver.h"

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
    gamecamera::GameCamera gameCamera(detectionConfig);
    gameresolver::GameResolver gameResolver;
    while (gameCamera.GetRunning()&&!gameOver)
    {
        gameCamera.GetImage(frame);
        gameResolver.GetRoi(frame);
        gameResolver.SetControl(gameControl);
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