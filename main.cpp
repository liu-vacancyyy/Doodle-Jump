#include "game_camera/camera.h"
#include <thread>
#include <signal.h>
#include "game_common/common.h"
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
    gamecamera::GameCamera gameCamera(detectionConfig);
    gameresolver::GameResolver gameResolver;
    while (!gameOver)
    {
        if(!gameCamera.GetRunning()){
            std::cout<<"Get frame failed!"<<std::endl;
        }else{
            gameCamera.GetImage(frame);
            gameResolver.GetRoi(frame,gameCamera.GetFrameTime());
            gameResolver.SetControl();
            if(detectionConfig.GetDebug()){
                cv::imshow("detection",frame);
                cv::waitKey(1);
            }
        }
    }
}

int main(){
    signal(SIGINT, signalHandler);
    std::thread gameThread(GamePlaying);
    std::thread detectionThread(DetectionRunning);
    gameThread.join();
    detectionThread.join();
    return 0;
}