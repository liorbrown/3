// liorbrown@outlook.co.il

#include "Player.hpp"

void Player::bribe()
{    
    this->coins -= 4;
    this->isBribe = true;
}

void Player::sanction(Player* selected)
{
    this->coins -= 3;
    selected->sanctioned();
}

void Player::coup(Player* selected)
{
    this->coins -= 7;
    PlayersList::getInstance().remove(selected);
}

bool Player::arrested()
{
    if (this->coins)
    {
        --*this;
        ++*PlayersList::getInstance().current();
        this->arrestedTurn = Game::getInstance().getTurnNum();

        return true;
    }

    return false;
}

Player& Player::operator--()
{
    if (this->coins)
        --this->coins;

    return *this;
}

Player& Player::operator++()
{
    ++this->coins;
    return *this;
}