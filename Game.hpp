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
        
    public:
        static Game& getIstance();
        static void free();
        
        void start();
        string winner() const {return this->winnerName;}
        size_t getTurn() const {return this->turnNum;}

        void turn() const {
            cout << "\n😎-------------😎\n" << this->turnName << " turn:\n😎-------------😎" << endl;}
};