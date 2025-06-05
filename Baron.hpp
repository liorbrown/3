// liorbrown@outlook.co.il
#pragma once

#include "Player.hpp"

class Baron : public Player
{
    private:
        void sanctioned();
        
    public:
        Baron(string name): Player(name){this->ability = Player::EXCHANGE;}
};