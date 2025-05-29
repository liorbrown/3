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
        string winnerName;

        Game(){}
        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;
        
    public:
        static Game& getInstance();
        static void free();
        
        void start();
        string winner() const {return this->winnerName;}
        void turn() const; 
};