// liorbrown@outlook.co.il

#pragma once

#include "Player.hpp"

/// @brief This class represented player with the roll of Merchant
class Merchant : public Player
{
    private:
        /// @brief When Merchant have 3 coins on start of turn,
        /// his getting extra coin
        virtual void increaseCoins() {if (this->getCoins() >= 3) ++*this;}
        
        virtual bool arrested();

    public:
        Merchant(string name): Player(name){}
};