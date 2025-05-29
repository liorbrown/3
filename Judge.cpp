// liorbrown@outlook.co.il

#include "Judge.hpp"

bool Judge::blockBribe()
{
    string yesNo;

    cout << this->getName() << ": Do you want to block bribe? (y/n): ";
    cin >> yesNo;

    return (yesNo == "y");
}

void Judge::sanctioned()
{
    Player::sanctioned();

    --*PlayersList::getInstance().current();
}