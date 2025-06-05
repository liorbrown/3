// liorbrown@outlook.co.il

#include "Baron.hpp"

void Baron::sanctioned()
{
    Player::sanctioned();
    ++*this;
}