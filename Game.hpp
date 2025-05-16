// liorbrown@outlook.co.il
#pragma once

#include "PlayersList.hpp"
#include <string>
#include <map>

using namespace std;

class Game
{
    private:
        char* winnerName;

    public:
        Game(): winnerName(nullptr){}
        void start();
        char* winner();
};