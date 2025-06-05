// liorbrown@outlook.co.il

#include "Merchant.hpp"

bool Merchant::arrested()
{
    bool isArrested = Player::arrested();

    if (isArrested)
    {
        --*this;
        --*PlayersList::getInstance().current();
    }

    return isArrested;
}