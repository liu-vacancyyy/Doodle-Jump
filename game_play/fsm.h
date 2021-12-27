#ifndef GAME_FSM_H
#define GAME_FSM_H
#include <SFML/Graphics.hpp>
#include "../game_common/common.h"
#include <cstdlib>
#include <time.h>

namespace gameplay{
    class GameFSM
    {
    public:
        GameFSM();

        /**************************************************************************
         * @name            StateChange
         * @brief           状态转移
         ***************************************************************************/
        void StateChange();

    private:
        /**************************************************************************
         * @name            StartEvent
         * @brief           事件触发
         ***************************************************************************/
        void EventJudge();

        /**************************************************************************
         * @name            StartRunning
         * @brief           开始界面运行逻辑
         ***************************************************************************/
        void StartRunning();

        /**************************************************************************
         * @name            ReadyRunning
         * @brief           准备界面运行逻辑
         ***************************************************************************/
        void ReadyRunning();

        /**************************************************************************
         * @name            JumpRunning
         * @brief           跳跃界面运行逻辑
         ***************************************************************************/
        void JumpRunning();

        /**************************************************************************
         * @name            OverRunning
         * @brief           游戏结束界面运行逻辑
         ***************************************************************************/
        void OverRunning();

        /**************************************************************************
         * @name            CorrectOutside
         * @brief           出界修正
         * 
         * @param           [in] doodle的x坐标
         * @return           修正后的x坐标
         ***************************************************************************/
        int CorrectOutside(int doodle_x);

        /**************************************************************************
         * @name            TestRunning
         * @brief           测试模式运行逻辑
         ***************************************************************************/
        void TestRunning();         

        /******************数据寄存器******************/
        GAMESTATE game_state_;
        sf::RenderWindow* window_;
        sf::Event event_;
        std::vector<GamePlat> game_plats_;
        bool play_press_=false;
        bool again_press_=false;
        int ready_cnt_=0;
        int jump_height_=0;
        int velocity_=-10;

        /******************游戏素材变量******************/
        sf::Sprite bg_;
        sf::Sprite over_;
        sf::Sprite doodle_;
        sf::Sprite green_plat_;
        sf::Sprite white_plat_;
        sf::Sprite blue_plat_;
        sf::Sprite play_button_;
        sf::Sprite top_bar_;

        sf::Texture bg_texture_;
        sf::Texture over_texture_;
        sf::Texture doodle_left_texture_;
        sf::Texture doodle_right_texture_;
        sf::Texture green_plat_texture_;
        sf::Texture white_plat_texture_;
        sf::Texture blue_plat_texture_;
        sf::Texture play_button_texture_;
        sf::Texture top_bar_texture_;

        /******************常用变量******************/
        int fps_;
        GAMEMODE game_mode_;
        int window_length_=400;
        int window_height_=650;
        int green_plat_number_=20;
        int blue_plat_number_=3;
        int white_plat_number_=3;
        int max_height_=350;
    };
}
#endif