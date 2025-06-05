// liorbrown@outlook.co.il

#include "General.hpp"

bool General::arrested()
{
    bool isArrested = Player::arrested();
    
    if (isArrested)
        ++*this;

    return isArrested;
}