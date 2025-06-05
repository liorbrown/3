// liorbrown@outlook.co.il
#pragma once

#include "Player.hpp"

/// @brief This class represented player with the roll of  General
class General : public Player
{
    private:
        bool arrested();

    public:
        General(string name): Player(name){this->ability = BLOCK_COUP;}
};