// liorbrown@outlook.co.il

#include "Player.hpp"

void Player::playTurn()
{
    cout << "-------------" << endl;
    Game::getIstance().turn();
    cout << " turn:\n-------------" << endl;

    this->specialAction();
    
    size_t oppCode = 0;

    if (this->coins >= 10)
    {
        cout << "You have at least 10 coins so you have to coup" << endl;
        oppCode = 6;
    }
    else
    {
        while(!oppCode)
        {
            cout << "You have: " << this->coins << " coins\nChoose your action:\n1) Gather\n2) Tax\n3) Bribe\n4) Arrest\n5) Sanction\n6) Coup" << endl; 
            cin >> oppCode;

            if (oppCode < 1 || oppCode > 6 )
            {
                cout << "Wrong input 🙄";
                oppCode = 0;
            }
        }     
    }

    switch (oppCode)
    {
        case 1:
            this->gather();
            break;
        case 2:
            this->tax();
            break;
        case 3:
            this->bribe();
            break;
        case 4:
            this->arrest();
            break;
        case 5:
            this->sanction();
            break;
        case 6:
            this->coup();
            break;
    }

    this->isSanctioned = this->blockArrest = false;
}

void Player::gather()
{
    if (this->isSanctioned)
    {
        cout << "You are sanctioned, can't use gather or tax😶" << endl;
        this->playTurn();
        return;
    }

    ++*this;
}

bool Player::tax()
{
    if (this->isSanctioned)
    {
        cout << "You are sanctioned, can't use gather or tax😶" << endl;
        this->playTurn();
        return false;
    }

    for 
    (
        auto peersIterator = PlayersList::getInstance().pBegin(this->name);
        peersIterator != PlayersList::getInstance().pEnd();
        ++peersIterator
    )
        if (peersIterator->blockTax())
        {
            cout << "You been blocked by " << peersIterator->name << endl;
            return false;
        }
    
    this->coins += 2;

    return true;
}

void Player::bribe()
{
    if (this->isBribe)
        cout << "Can't bribe 2 times a row" << endl;
    else if (this->coins < 4)
        cout << "You need 4 coins for bribe, and you got only " << this->coins << endl;
    else
    {
        this->coins -= 4;

        for 
        (
            auto peersIterator = PlayersList::getInstance().pBegin(this->name);
            peersIterator != PlayersList::getInstance().pEnd();
            ++peersIterator
        )
            if (peersIterator->blockBribe())
                return;

        this->isBribe = true;
    }

    this->playTurn();
}

void Player::arrest()
{
    if (this->blockArrest)
    {
        cout << "You can't arrest because you blocked by spy 🕵🏻‍♂️" << endl;
        this->playTurn();
        return;
    }

    Player* selectedPlayer = this->choosePlayer();

    if (selectedPlayer->arrestedTurn &&
        Game::getIstance().getTurnNum() - selectedPlayer->arrestedTurn == 1)
    {
        cout << selectedPlayer->name << " already arrested in previous turn 😶" << endl;
        this->playTurn();
        return;
    }

    if (!selectedPlayer->coins)
    {
        cout << selectedPlayer->name << " don't have any coins😶" << endl;
        this->playTurn();
        return;
    }

    selectedPlayer->arrested();
}

void Player::sanction()
{
    if (this->coins < 3)
    {
        cout << "You need 3 coins for sanction";
        this->playTurn();
        return;
    }

    Player* selectedPlayer = this->choosePlayer();

    if (selectedPlayer->isSanctioned)
    {
        cout << selectedPlayer->name << " already sanctioned 😶" << endl;
        this->playTurn();
        return;
    }

    this->coins -= 3;
    selectedPlayer->sanctioned();
}

void Player::coup()
{
    if (this->coins < 7)
    {
        cout << "You need 7 coins for sanction" << endl;
        this->playTurn();
        return;
    }

    this->coins -= 7;

    Player* selected = this->choosePlayer();

    for 
    (
        auto peersIterator = PlayersList::getInstance().pBegin(this->name);
        peersIterator != PlayersList::getInstance().pEnd();
        ++peersIterator
    )
        if (peersIterator->blockCoup())
            return;

    PlayersList::getInstance().remove(selected);
}

void Player::arrested()
{
    --*this;
    ++*PlayersList::getInstance().current();

    this->arrestedTurn = Game::getIstance().getTurnNum();
}

Player* Player::choosePlayer()
{
    string PlayerName;
    Player* selectedPlayer = nullptr;

    while (!selectedPlayer)
    {
        cout << "Choose player:\n";

        for 
        (
            auto peersIterator = PlayersList::getInstance().pBegin(this->name);
            peersIterator != PlayersList::getInstance().pEnd();
            ++peersIterator
        )
            cout << peersIterator->name << endl;
        
        cin >> PlayerName;

        if (PlayerName == this->name)
            cout << "Can't do opearation on your self 🫤";
        else
        {
            selectedPlayer = PlayersList::getInstance().getPlayer(PlayerName);

            if (!selectedPlayer)
                cout << "Player not exist, please try again" << endl;
        }
    }

    return selectedPlayer;
}

Player& Player::operator--()
{
    --this->coins;
    return *this;
}

Player& Player::operator++()
{
    ++this->coins;
    return *this;
}