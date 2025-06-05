// liorbrown@outlook.co.il
#pragma once

#include "Player.hpp"

class Governor : public Player
{
    private:
        void tax(){this->getCoins() += 3;}

    public:
        Governor(string name): Player(name){this->ability = BLOCK_TAX;}
};