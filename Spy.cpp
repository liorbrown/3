// liorbrown@outlook.co.il

#include "Spy.hpp"

void Spy::specialAction()
{
    string yesNo;

    cout << "Do you want to spy someone? (y/n): ";
    cin >> yesNo;

    if (yesNo == "y")
    {
        Player* selected = this->choosePlayer();

        cout << selected->getName() << " have " << this->coins << 
            " coins\nDo you want to block his able to arrest next turn? (y/n): ";

        cin >> yesNo;

        if (yesNo == "y")
            selected->arrestBlocking();
    }
}