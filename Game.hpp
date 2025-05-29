// liorbrown@outlook.co.il
#pragma once

#include <string>
#include <map>
#include <iostream>
#include "PlayersList.hpp"

using namespace std;

class Game
{
    private:
        static Game* instance;

        string turnName;
        size_t turnNum; 
        string winnerName;

        Game(): turnNum(0){}
        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;
        
    public:
        static Game& getIstance();
        static void free();
        
        void start();
        string winner() const {return this->winnerName;}
        size_t getTurnNum() const {return this->turnNum;}
        string getTurnName() const {return this->turnName;}

        void turn() const {cout << this->turnName;}
};