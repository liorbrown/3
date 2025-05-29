// liorbrown@outlook.co.il
#pragma once

#include "Player.hpp"

class Judge : public Player
{
    private:
        bool blockBribe();
        void sanctioned();

    public:
        Judge(string name): Player(name){}
};