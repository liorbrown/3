// liorbrown@outlook.co.il

#include <cassert>
#include <iostream>
#include <sstream>
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

string PlayersList::getListString()
{
    stringstream result;

    for (const Player* p : this->list)
        result << p->getName() << " the " << (typeid(*p).name() + 1) << '\n';

    return result.str();
}

bool PlayersList::newPlayer(string name)
{
    if (this->getPlayer(name))
        return false;
    
    srand(time(NULL));
    
    int roll = rand() % 6;

    switch (roll)
    {
        case 0:
            return (this->list.emplace_back(new Baron{name}));
        case 1:
            return (this->list.emplace_back(new Governor{name}));
        case 2:
            return (this->list.emplace_back(new General{name}));
        case 3:
            return (this->list.emplace_back(new Spy{name}));
        case 4:
            return (this->list.emplace_back(new Merchant{name}));
        case 5:
            return (this->list.emplace_back(new Judge{name}));
    }
}

Player* PlayersList::getNext()
{   
    if (!this->turnsIterator.base()) 
        this->turnsIterator = this->list.begin();
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

PlayersList::iterator::iterator(vector<Player *>::iterator current):
    current(current)
{
    if (this->current == PlayersList::getInstance().list.begin() &&
        *this->current == PlayersList::getInstance().current())
            ++this->current;
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