// liorbrown@outlook.co.il
#pragma once

#include "Player.hpp"

/// @brief This class represented player with the roll of Spy
class Spy : public Player
{
    public:
        Spy(string name): Player(name){this->ability = Player::SPYING;}       
};