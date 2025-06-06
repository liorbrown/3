// liorbrown@outlook.co.il

#include "Judge.hpp"
#include "PlayersList.hpp"

void Judge::    sanctioned()
{
    Player::sanctioned();
    --*PlayersList::getInstance().current();
}