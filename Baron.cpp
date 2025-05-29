// liorbrown@outlook.co.il

#include "Baron.hpp"

void Baron::specialAction()
{
    if (this->coins >= 3)
    {
        string yesNo;

        cout << "Do you want to exchange 3 coins by 6? (y/n): ";
        cin >> yesNo;

        if (yesNo == "y")
            this->coins += 3;
    }
}

void Baron::sanctioned()
{
    Player::sanctioned();
    ++*this;
}