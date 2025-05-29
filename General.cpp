// liorbrown@outlook.co.il

#include "General.hpp"

bool General::blockCoup()
{
    if (this->coins >= 5)
    {
        string yesNo;
        cout << this->getName() << ": Do you want to block the coup? (y/n): ";
        cin >> yesNo;

        if (yesNo == "y")
        {
            this->coins -= 5;
            return true;
        }
    }

    return false;
}