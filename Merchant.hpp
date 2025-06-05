// liorbrown@outlook.co.il

#pragma once

#include "Player.hpp"

class Merchant : public Player
{
    private:
        void increaseCoins() {if (this->getCoins() >= 3) ++*this;}
        bool arrested();

    public:
        Merchant(string name): Player(name){}
};