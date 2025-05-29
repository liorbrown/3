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

PlayersList &PlayersList::getInstance()
{
    if (!instance)
        instance = new PlayersList;
    
    return *instance;
}

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

void PlayersList::init()
{
    this->turnNum = 0;
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

    this->turnsIterator = this->list.begin();
}

Player *PlayersList::createPlayer(string name)
{
    srand(time(NULL));
    
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

Player* PlayersList::getNext()
{
    if (this->list.empty())
        this->init();
    else if (this->list.size() == 1)
        return nullptr;
    else if (this->current()->getIsBribe())
        this->current()->Unbribe();
    else
    {
        ++this->turnsIterator;

        if (this->turnsIterator == this->list.end())
            this->turnsIterator = this->list.begin();
    }

    ++this->turnNum;

    return *this->turnsIterator;
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

    for(auto p = this->list.begin(); p != this->list.end();++p)
        if (*p == player)
        {
            this->list.erase(p);
            break;
        }
    
    delete player;

    Player* current = PlayersList::getInstance().current();
    
    for
    (
        this->turnsIterator = this->list.begin();
        *this->turnsIterator != current;
        ++this->turnsIterator
    );
}

PlayersList::iterator& PlayersList::iterator::operator++() 
{
    auto next = ++current;

    if (next != PlayersList::getInstance().list.end() && 
        *next == PlayersList::getInstance().current())
        ++current;

    return *this;
}

// i++;
// Usually iterators are passed by value and not by const& as they are small.
const PlayersList::iterator PlayersList::iterator::operator++(int) 
{
    iterator tmp = *this;
    ++*this;
    return tmp;
}

PlayersList::iterator::iterator(vector<Player *>::iterator current):
    current(current)
{
    if (this->current == PlayersList::getInstance().list.begin() &&
        *this->current == PlayersList::getInstance().current())
            ++this->current;
}