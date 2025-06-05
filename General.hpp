// liorbrown@outlook.co.il
#pragma once

#include "Player.hpp"

class General : public Player
{
    private:
        bool arrested();

    public:
        General(string name): Player(name){this->ability = BLOCK_COUP;}
};