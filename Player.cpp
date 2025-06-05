// liorbrown@outlook.co.il

#include "Player.hpp"
#include "PlayersList.hpp"

void Player::bribe()
{    
    this->coins -= 4;
    this->isBribe = true;
}

void Player::sanction(Player* selected)
{
    this->coins -= 3;

    // Call sanctioned() on selected player
    selected->sanctioned();
}

void Player::coup(Player* selected)
{
    this->coins -= 7;

    // Eliminate player by Removing his player from the players list
    PlayersList::getInstance().remove(selected);
}

bool Player::arrested()
{
    // If this player don't have coins, nothing happend and the arresting player lose its turn
    if (this->coins)
    {
        // Deacrease this
        --*this;
        // Increase current turn player (not this player)
        ++*PlayersList::getInstance().current();

        // Sets this player arrestedTurn to this turn.
        // For knowing to not allow arrest him in the next turn
        this->arrestedTurn = PlayersList::getInstance().getTurn();

        return true;
    }

    return false;
}

Player& Player::operator--()
{
    // If player donwt have coins, so nothing happens
    if (this->coins)
        --this->coins;

    return *this;
}

Player& Player::operator++()
{
    ++this->coins;
    return *this;
}