// liorbrown@outlook.co.il

#include "General.hpp"

/// @brief After General arrested he gett back is coin
/// @return True - if arrest success, false - otherwise
bool General::arrested()
{
    bool isArrested = Player::arrested();
    
    // If arrest succeed, return general his coin
    if (isArrested)
        ++*this;

    return isArrested;
}