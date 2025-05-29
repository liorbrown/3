// liorbrown@outlook.co.il

#include "Governor.hpp"

bool Governor::tax()
{
    bool result = Player::tax();
    
    if (result)
        ++*this;

    return result;
}

bool Governor::blockTax()
{
    string yesNo;

    cout << this->getName() << ": Are you want to block ";
    Game::getInstance().turn();
    cout << " from doing tax? (y/n)";

    cin >> yesNo;

    return (yesNo == "y");
}
