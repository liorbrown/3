// liorbrown@outlook.co.il
#pragma once

#include "Player.hpp"

class Spy : public Player
{
    public:
        Spy(string name): Player(name){this->ability = Player::SPYING;}       
};