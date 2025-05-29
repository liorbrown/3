// liorbrown@outlook.co.il
#pragma once

#include "Player.hpp"

class Merchant : public Player
{
    private:
        void specialAction() {if (this->coins >= 3) ++*this;}
        void arrested();

    public:
        Merchant(string name): Player(name){}
};