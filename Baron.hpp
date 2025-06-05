// liorbrown@outlook.co.il

#pragma once

#include "Player.hpp"

/// @brief This class represented player with the roll of  Baron
class Baron : public Player
{
    private:
        /// @brief Baron gets coin when sanctioned
        virtual void sanctioned();
        
    public:
        Baron(string name): Player(name){this->ability = Player::EXCHANGE;}
};