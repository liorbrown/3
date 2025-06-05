// liorbrown@outlook.co.il
#pragma once

#include "Player.hpp"

/// @brief This class represented player with the roll of Judge
class Judge : public Player
{
    private:
        /// @brief When judge sanctioned, the player who sanction it lose additional coin
        virtual void sanctioned();

    public:
        Judge(string name): Player(name){this->ability = BLOCK_BRIBE;}
};