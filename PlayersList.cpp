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
    for (pair<string, Player*> p : this->list)
        delete p.second;
    
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
    size_t nPlayers;

    do
    {
        cout << "Please enter number of players (2-6): ";
        cin >> nPlayers;

        //nPlayers = stoul(playerNum);

        if (nPlayers < 2 || nPlayers > 6)
        {
            cout << "Wrong input 🙄";
            nPlayers = 0;
        }
    } while (!nPlayers);

    for (size_t i = 1; i <= nPlayers; i++)
    {
        string playerName;

        while (playerName.empty())
        {
            cout << "Enter player " << i << " name: ";
            cin >> playerName;

            if (this->list.find(playerName)->second)
            {
                cout << "Name is already taken🫤" << endl;
                playerName.clear();
            }
        }

        Player* newPlayer = createPlayer(playerName);

        this->list.emplace(playerName, newPlayer);

        cout << playerName << " is " << (typeid(*newPlayer).name() + 1) << endl;
    }
}

Player* PlayersList::getPlayer(const string &name) const
{
    return this->list.find(name)->second;
}

string* PlayersList::players() const
{
    string* pList = new string[this->list.size()];
    size_t i = 0;

    for (auto p : this->list)
        pList[i++] = p.first;
        
    return pList;
}

void PlayersList::remove(Player* player)
{
    this->list.erase(player->getName());

    delete player;
}

PlayersList::cycleIterator PlayersList::begin() 
{
    return (this->list.begin());
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
    map<string, Player*>& myList = PlayersList::getInstance().list;
    
    assert(myList.size());
    
    if (myList.size() == 1)
        this->current = {};
    else if ((*this)->getIsBribe())
        (*this)->getIsBribe() = false;
    else
    {
        ++this->current;

        if (this->current == myList.end())
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
    map<string, Player*>* myList = &PlayersList::getInstance().list;

    auto next = ++current;

    if (next != myList->end() && next->first == this->currentPlayer)
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

