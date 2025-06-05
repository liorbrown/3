// liorbrown@outlook.co.il
#pragma once

#include "Player.hpp"

class Judge : public Player
{
    private:
        void sanctioned();

    public:
        Judge(string name): Player(name){this->ability = BLOCK_BRIBE;}
};