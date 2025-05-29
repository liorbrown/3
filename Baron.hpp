// liorbrown@outlook.co.il
#pragma once

#include "Player.hpp"

class Baron : public Player
{
    private:
        void specialAction();
        void sanctioned();
        
    public:
        Baron(string name): Player(name){}
};