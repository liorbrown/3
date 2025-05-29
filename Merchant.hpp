// liorbrown@outlook.co.il
#pragma once

#include "Player.hpp"

class Merchant : public Player
{
    private:
        void specialAction() {if (this->coins >= 3) ++*this;}
        void arrested(){----*this;}

    public:
        Merchant(string name): Player(name){}
};