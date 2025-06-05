// liorbrown@outlook.co.il
#pragma once

#include "Player.hpp"

/// @brief This class represented player with the roll of Governor
class Governor : public Player
{
    private:

        /// @brief Governor gets extra coin for tax
        virtual void tax(){this->getCoins() += 3;}

    public:
        Governor(string name): Player(name){this->ability = BLOCK_TAX;}
};