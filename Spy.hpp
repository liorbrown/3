// liorbrown@outlook.co.il
#pragma once

#include "Player.hpp"

class Spy : public Player
{
    private:
        void specialAction();

    public:
        Spy(string name): Player(name){}
        
};