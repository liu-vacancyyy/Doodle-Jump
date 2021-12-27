#include "fsm.h"

namespace gameplay{
    GameFSM::GameFSM(){
        if(gameConfig.GetTestState()){
            game_state_=GAMESTATE::TEST;
        }else{
            game_state_=GAMESTATE::START;
        }
        game_mode_=GAMEMODE(gameConfig.GetMode());
        fps_=gameConfig.GetFPS();
        window_=new::sf::RenderWindow(sf::VideoMode(window_length_,window_height_),"Doodle Jump");
        window_->setFramerateLimit(fps_);
        bg_texture_.loadFromFile("../game_images/bg-grid.png");
        bg_.setTexture(bg_texture_);
        over_texture_.loadFromFile("../game_images/menu/gameover.png");
        over_.setTexture(over_texture_);
        over_.setScale(0.9,1);
        doodle_left_texture_.loadFromFile("../game_images/doodleL.png");
        doodle_right_texture_.loadFromFile("../game_images/doodleR.png");
        doodle_.setTexture(doodle_right_texture_);
        green_plat_texture_.loadFromFile("../game_images/p-green.png");
        green_plat_.setTexture(green_plat_texture_);
        blue_plat_texture_.loadFromFile("../game_images/p-blue.png");
        blue_plat_.setTexture(blue_plat_texture_);
        white_plat_texture_.loadFromFile("../game_images/p-white.png");
        white_plat_.setTexture(white_plat_texture_);
        play_button_texture_.loadFromFile("../game_images/menu/play-button.png");
        play_button_.setTexture(play_button_texture_);
        top_bar_texture_.loadFromFile("../game_images/topbar.png");
        top_bar_.setTexture(top_bar_texture_);
    }

    void GameFSM::StateChange(){
        while(window_->isOpen()){
            EventJudge();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                if(game_mode_!=GAMEMODE::FACE){
                    gameControl.direction=-1;
                    gameControl.speed=1;
                }
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                if(game_mode_!=GAMEMODE::FACE){
                    gameControl.direction=1;
                    gameControl.speed=1;
                }
            }
            switch(game_state_){
                case GAMESTATE::START:
                    StartRunning();
                    break;
                case GAMESTATE::READY:
                    ReadyRunning();
                    break;
                case GAMESTATE::JUMP:
                    //JumpRunning();
                    break;
                case GAMESTATE::OVER:
                    OverRunning();
                    break;

                /******************这部分case仅在测试一些逻辑使用，正常游戏不会进入******************/
                case GAMESTATE::TEST:
                    TestRunning();
                    break;
                /****************************************************************************************/

                default:
                    break;
            }
            window_->display();
            gameControl.direction=0;
            gameControl.speed=0;
        }
    }

    void GameFSM::EventJudge(){
        while (window_->pollEvent(event_))
        {
            if (event_.type == sf::Event::Closed){
                gameClose=true;
                window_->close();
            }
            if(game_state_==GAMESTATE::START){
                if(event_.type=sf::Event::MouseButtonPressed){
                    if(event_.key.code==sf::Mouse::Left){
                        if(sf::Mouse::getPosition().x-window_->getPosition().x>play_button_.getPosition().x&&
                            sf::Mouse::getPosition().x-window_->getPosition().x<(window_length_-play_button_.getPosition().x)&&
                            sf::Mouse::getPosition().y-window_->getPosition().y>play_button_.getPosition().y&&
                            sf::Mouse::getPosition().y-window_->getPosition().y<(window_height_-play_button_.getPosition().y)){
                            play_press_=true;
                        }
                    }
                }
            }else if(game_state_==GAMESTATE::OVER){
                if(event_.type=sf::Event::MouseButtonPressed){
                    if(event_.key.code==sf::Mouse::Left){
                        if(sf::Mouse::getPosition().x-window_->getPosition().x>60&&
                            sf::Mouse::getPosition().x-window_->getPosition().x<200&&
                            sf::Mouse::getPosition().y-window_->getPosition().y>190&&
                            sf::Mouse::getPosition().y-window_->getPosition().y<240){
                            again_press_=true;
                        }
                    }
                }
            }
        }
    }

    void GameFSM::StartRunning(){
        if(play_press_){
            game_state_=GAMESTATE::READY;
            play_press_=false;
            return;
        }
        window_->draw(bg_);
        play_button_.setPosition(window_length_/2-int((play_button_texture_.getSize().x)/2),
                                                            window_height_/2-int((play_button_texture_.getSize().y)/2));
        window_->draw(play_button_);
    }

    void GameFSM::ReadyRunning(){
        if(ready_cnt_==fps_*0.5){
            game_state_=GAMESTATE::JUMP;
            ready_cnt_=0;
            return;
        }
        if(ready_cnt_==0){
            std::vector<GamePlat>().swap(game_plats_);
            window_->draw(bg_);
            window_->draw(top_bar_);
            std::srand(std::time(NULL));
            for(int i=0;i<20;i++){
                green_plat_.setPosition(std::rand()%(window_length_-green_plat_texture_.getSize().x+1),
                                                                    std::rand()%31+window_height_-(i+1)*30-green_plat_texture_.getSize().y);
                window_->draw(green_plat_);
                GamePlat game_plat_temp;
                game_plat_temp.color=PLATCOLOR::GREEN;
                game_plat_temp.x=green_plat_.getPosition().x;
                game_plat_temp.y=green_plat_.getPosition().y;
                game_plat_temp.on=true;
                game_plats_.push_back(game_plat_temp);
            }
            doodle_.setPosition(game_plats_[0].x,game_plats_[0].y-doodle_right_texture_.getSize().y);
            window_->draw(doodle_);
        }
        ready_cnt_++;
    }

    void GameFSM::JumpRunning(){
        if(doodle_.getPosition().y>window_height_){
            game_state_=GAMESTATE::OVER;
            return;
        }
        for(int i=0;i<game_plats_.size();i++){
            if(doodle_.getPosition().x<(game_plats_[i].x+green_plat_texture_.getSize().x-doodle_left_texture_.getSize().x+5)&&
                doodle_.getPosition().x>(game_plats_[i].x-5)&&
                doodle_.getPosition().y>=game_plats_[i].y&&
                doodle_.getPosition().y<=(game_plats_[i].y+green_plat_texture_.getSize().y)&&velocity_>0){
                velocity_=-10;
                break;
            }
        }
        if(gameControl.direction==-1){
            doodle_.setTexture(doodle_left_texture_);
            doodle_.setPosition(CorrectOutside(doodle_.getPosition().x-gameControl.speed),doodle_.getPosition().y);
        }else if(gameControl.direction==1){
            doodle_.setTexture(doodle_right_texture_);
            doodle_.setPosition(CorrectOutside(doodle_.getPosition().x+gameControl.speed),doodle_.getPosition().y);
        }
        window_->draw(bg_);
        window_->draw(top_bar_);
        if(doodle_.getPosition().y>max_height_){
            for(int i=0;i<game_plats_.size();i++){
                game_plats_[i].y-velocity_;
                if(game_plats_[i].y>window_height_){
                    game_plats_[i].x=std::rand()%(window_length_-green_plat_texture_.getSize().x+1);
                    game_plats_[i].y=std::rand()%31+50-green_plat_texture_.getSize().y;
                    if(game_plats_[i].on){
                        switch (game_plats_[i].color)
                        {
                        case GREEN:
                            green_plat_.setPosition(game_plats_[i].x,game_plats_[i].y);
                            window_->draw(green_plat_);
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
            doodle_.setPosition(doodle_.getPosition().x,max_height_);
            window_->draw(doodle_);
        }else{
            for(int i=0;i<game_plats_.size();i++){
                if(game_plats_[i].on){
                    switch (game_plats_[i].color)
                    {
                    case GREEN:
                        green_plat_.setPosition(game_plats_[i].x,game_plats_[i].y);
                        window_->draw(green_plat_);
                        break;
                    default:
                        break;
                    }
                }
            }
            doodle_.setPosition(doodle_.getPosition().x,doodle_.getPosition().y+velocity_);
            window_->draw(doodle_);
        }
        velocity_=velocity_+1;
    }

    void GameFSM::OverRunning(){
        if(again_press_){
            game_state_=GAMESTATE::START;
            again_press_=false;
            return;
        }
        window_->draw(over_);
    }

    int GameFSM::CorrectOutside(int doodle_x){
        if(doodle_x>=window_length_){
            doodle_x=doodle_x-window_length_;
        }else if(doodle_x<=(-int(doodle_left_texture_.getSize().x))){
            doodle_x=window_length_+doodle_x;
        }
        return doodle_x;
    }

    void GameFSM::TestRunning(){

    }
}