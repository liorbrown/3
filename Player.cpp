// liorbrown@outlook.co.il

#include "Player.hpp"
#include "PlayersList.hpp"

void Player::gather()
{
    // Validate action
    if (this->isSanctioned)
        throw logic_error("Sanctioned player can't gather");

    ++*this;
}

void Player::tax()
{
    // Validate action
    if (this->isSanctioned)
        throw logic_error("Sanctioned player can't tax");
        
    this->coins += 2;
}

void Player::bribe()
{    
    // Validate action
    if (!PlayersList::getInstance().getTurn())
        throw runtime_error("Can't bribe when game not active");
    if (this->coins < 4)
        throw logic_error("Need 4 coins for bribe");
    if (this->isBribe)
        throw logic_error("Can't bribe 2 times a row");

    this->coins -= 4;
    this->isBribe = true;
}

void Player::sanction(Player* selected)
{
    // Validate action
    if (!selected)
        throw invalid_argument("Selected player can't be null");
    if (this == selected)
        throw invalid_argument("Can't sanction yourself");
    if (this->coins < 3)
        throw logic_error("Need 3 coins for sanction");

    this->coins -= 3;

    // Call sanctioned() on selected player
    selected->sanctioned();
}

void Player::coup(Player* selected)
{
    // Validate action
    if (!selected)
        throw invalid_argument("Selected player can't be null");
    if (this == selected)
        throw invalid_argument("Can't coup yourself");
    if (this->coins < 7)
        throw logic_error("Need 7 coins for sanction");

    this->coins -= 7;

    // Eliminate player by Removing his player from the players list
    PlayersList::getInstance().remove(selected);
}

bool Player::arrested()
{
    if (this == PlayersList::getInstance().current())
        throw logic_error("You can't arrest your self 🫤");

    if (this->getArrestedTurn() &&
        PlayersList::getInstance().getTurn() - this->getArrestedTurn() == 1)
        throw logic_error("Can't arrest same player 2 turns a row 🫤");

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