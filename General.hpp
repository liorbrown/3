// liorbrown@outlook.co.il
#pragma once

#include "Player.hpp"

class General : public Player
{
    private:
        bool blockCoup();
        void arrested(){++*PlayersList::getInstance().current();}

    public:
        General(string name): Player(name){}
};