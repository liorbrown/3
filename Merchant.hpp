// liorbrown@outlook.co.il

#pragma once

#include "Player.hpp"

/// @brief This class represented player with the roll of Merchant
class Merchant : public Player
{
    private:
        /// @brief When Merchant have 3 coins on start of turn,
        /// his getting extra coin
        void increaseCoins() {if (this->getCoins() >= 3) ++*this;}
        bool arrested();

    public:
        Merchant(string name): Player(name){}
};