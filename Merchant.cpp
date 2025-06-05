// liorbrown@outlook.co.il

#include "Merchant.hpp"
#include "PlayersList.hpp"

/// @brief When merchant arrested, the player that arrest him not get coins
/// but he lose 2
/// @return True - if arrest succeed, false - otherwise
bool Merchant::arrested()
{
    bool isArrested = Player::arrested();

    // Only if arrest succeed decrease players coins
    if (isArrested)
    {
        --*this;
        --*PlayersList::getInstance().current();
    }

    return isArrested;
}