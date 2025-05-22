// liorbrown@outlook.co.il

#include <cassert>
#include <iostream>
#include "PlayersList.hpp"
#include "Baron.hpp"
#include "Spy.hpp"
#include "Governor.hpp"
#include "Judge.hpp"
#include "Merchant.hpp"
#include "General.hpp"
#include "Game.hpp"

PlayersList* PlayersList::instance = nullptr;

void PlayersList::free()
{
    if (instance)
    {
        delete instance;
        instance = nullptr;
    } 
}

void PlayersList::clear()
{
    for (Player* p : this->list)
        delete p;
    
    this->list.clear();
}

Player *PlayersList::createPlayer(string name)
{
    int roll = rand() % 6;

    switch (roll)
    {
        case 0:
            return (new Baron{name});
        case 1:
            return (new Governor{name});
        case 2:
            return (new General{name});
        case 3:
            return (new Spy{name});
        case 4:
            return (new Merchant{name});
        case 5:
            return (new Judge{name});
        default:
            return nullptr;
    }
}

PlayersList &PlayersList::getInstance()
{
    if (!instance)
        instance = new PlayersList;
    
    return *instance;
}

void PlayersList::init()
{
    this->clear();

    string playerNum;
    size_t nPlayers = 0;

    while (!nPlayers)
    {
        cout << "Please enter number of players (2-6): ";
        cin >> nPlayers;

        if (nPlayers < 2 || nPlayers > 6)
        {
            cout << "Wrong input 🙄" << endl;
            nPlayers = 0;
        }
    }

    for (size_t i = 1; i <= nPlayers; i++)
    {
        string playerName;

        while (playerName.empty())
        {
            cout << "Enter player " << i << " name: ";
            cin >> playerName;

            if (this->getPlayer(playerName))
            {
                cout << "Name is already taken🫤" << endl;
                playerName.clear();
            }
        }

        Player* newPlayer = createPlayer(playerName);

        this->list.emplace_back(newPlayer);

        cout << playerName << " is " << (typeid(*newPlayer).name() + 1) << endl;
    }
}

Player* PlayersList::getPlayer(const string &name) const
{
    for(Player* p: this->list)
        if (p->getName() == name)
            return p;
    
    return nullptr;
}

string* PlayersList::players() const
{
    string* pList = new string[this->list.size()];
    size_t i = 0;

    for (const Player* p : this->list)
        pList[i++] = p->getName();
        
    return pList;
}

void PlayersList::remove(Player* player)
{
    size_t nPlayers = this->list.size();

    for (size_t i = 0; i < nPlayers; i++)
        if (this->list.at(i) == player)
        {
            this->list.erase(this->list.begin()+i);
            delete player;
            return;
        }
}

PlayersList::peersIterator PlayersList::pBegin(string currentPlayer)
{
    PlayersList::peersIterator iterator{this->list.begin(), currentPlayer};

    if (iterator->getName() == currentPlayer)
        ++iterator;
    
    return iterator;
}

PlayersList::cycleIterator& PlayersList::cycleIterator::operator++()
{
    vector<Player*>& myList = PlayersList::getInstance().list;
    
    assert(myList.size());
    
    if (myList.size() == 1)
        this->current = {};
    else if ((*this)->getIsBribe())
        (*this)->getIsBribe() = false;
    else
    {
        ++this->current;

        if (!*this->current)
            this->current = myList.begin();
    }

    return (*this);
}

// i++;
// Usually iterators are passed by value and not by const& as they are small.
const PlayersList::cycleIterator PlayersList::cycleIterator::operator++(int) {
    cycleIterator tmp = *this;
    ++*this;
    return tmp;
}

PlayersList::peersIterator& PlayersList::peersIterator::operator++() {
    auto next = ++current;

    if (next != PlayersList::getInstance().list.end() && 
        (*next)->getName() == this->currentPlayer)
        ++current;

    return *this;
}

// i++;
// Usually iterators are passed by value and not by const& as they are small.
const PlayersList::peersIterator PlayersList::peersIterator::operator++(int) {
    peersIterator tmp = *this;
    ++*this;
    return tmp;
}