#include "game_camera/camera.h"
#include <thread>
#include <signal.h>
#include "game_common/common.h"
#include "game_resolver/resolver.h"
#include "game_play/fsm.h"

using namespace sf;

void signalHandler(int signal){
    gameClose=true;
}

void GamePlaying(){
    gameplay::GameFSM gameFSM;
    if(!gameClose)
    {
        gameFSM.StateChange();
    }
    std::cout<<"Game Over!"<<std::endl;
}

void DetectionRunning(){
    cv::Mat frame;
    uint64_t camera_time;
    cv::VideoWriter videoWriter;
    gamecamera::GameCamera* gameCamera;
    if(detectionConfig.GetCameraId()!=-1)
        gameCamera=new::gamecamera::GameCamera(detectionConfig);
    gameresolver::GameResolver gameResolver;
    while (!gameClose)
    {
        if(!gameCamera->GetRunning()){
            std::cout<<"Get frame failed!"<<std::endl;
        }else{
            if(gameCamera->GetImage(frame,camera_time)){
                gameResolver.GetRoi(frame,camera_time);
                gameResolver.SetControl();
                if(detectionConfig.GetDebug()){
                    cv::imshow("detection",frame);
                    cv::waitKey(1);
                    // char key=cv::waitKey(1);
                    // if(key=='s'){
                    //     while(cv::waitKey(0)!='s')
                    //         cv::waitKey(0);
                    // }
                }
            }
        }
    }
}

int main(){
    signal(SIGINT, signalHandler);
    //std::thread gameThread(GamePlaying);
    std::thread detectionThread(DetectionRunning);
    //gameThread.join();
    detectionThread.join();
    return 0;
}