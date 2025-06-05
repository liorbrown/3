// liorbrown@outlook.co.il

#include "Judge.hpp"

void Judge::sanctioned()
{
    Player::sanctioned();

    --*PlayersList::getInstance().current();
}