// liorbrown@outlook.co.il

#include <iostream>
#include <sstream>
#include "PlayersList.hpp"
#include "Baron.hpp"
#include "Spy.hpp"
#include "Governor.hpp"
#include "Judge.hpp"
#include "Merchant.hpp"
#include "General.hpp"

// Init static singlton pointer to null
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
    this->turn = 0;

    // Runs on all players and free them
    for (Player* p : this->list)
        delete p;
    
    // Clear inner list
    this->list.clear();
}

string PlayersList::getListString()
{
    stringstream result;

    // Runs on all players and add row with player name and roll
    // The use of +1 is for skiping first char witch is the size of type name
    // preety ugly solution, will not work for size greater then 9
    // but its good enough for this litle game
    for (const Player* p : this->list)
        result << p->getName() << " the " << (typeid(*p).name() + 1) << '\n';

    return result.str();
}

bool PlayersList::newPlayer(string name)
{
    // Not alowing 2 players with same name because this is the way the players distinct between
    // other players when they want to make action on them etc.
    if (this->getPlayer(name))
        return false;
    
    // This action is like "shuffle" the dices
    // otherwise rand will pick the same results any game
    srand(time(NULL));
    
    int roll = rand() % 6;

    // Creates new player, insert it to end of list, and return true
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

    // The compiler warning me here for not return value in any case
    // But i know a little of math to know he is wrong
}

Player* PlayersList::getNext()
{   
    ++this->turn;

    // This is a way to check if iterator is in init mode
    // means its not pointing at nothing
    // means this is the first turn of the game
    if (!this->turnsIterator.base()) 
        this->turnsIterator = this->list.begin();
    // This is our indication of ending the game
    else if (this->list.size() == 1)
        return nullptr;
    // If current player is in bribe, so instead of forwarding to next player
    // we just unbribe him for his seconed turn
    else if (this->current()->getIsBribe())
        this->current()->Unbribe();
    // This is the regular situation
    else
    {
        ++this->turnsIterator;

        // If reaches end of list, return to te first player
        if (this->turnsIterator == this->list.end())
            this->turnsIterator = this->list.begin();
    }

    // Return pointer to player of new turn
    return *this->turnsIterator;
}

Player* PlayersList::getPlayer(const string &name) const
{
    // Runs on all players in the list, and return pointer to the one with given name
    for(Player* p: this->list)
        if (p->getName() == name)
            return p;
    
    // If not found return null
    return nullptr;
}

void PlayersList::remove(Player* player)
{
    // Runs on all players in list
    // This time run with regular for and not foreach
    // because need to iterator itself for the erase method
    for(auto p = this->list.begin(); p != this->list.end();++p)
        // Equale beetwen adresses to ensure this is exactly same object
        if (*p == player)
        {
            // Remove player from list
            this->list.erase(p);
            break;
        }
    
    // Free object memory
    delete player;

    // This is very problematic issue with standard iterators.
    // after list.erase(p) the iterator is unpredictible 
    // because it is sets to previous state of  the container.
    // So the solution is to keep pointer to current player
    // and then runs iterator from list.begin() to current player
    // and this is refresh iterator to current container state
    Player* current = PlayersList::getInstance().current();
    
    for
    (
        this->turnsIterator = this->list.begin();
        *this->turnsIterator != current;
        ++this->turnsIterator
    );
}

string* PlayersList::players() const
{
    string* pList = new string[this->list.size()];
    size_t i = 0;

    // Runs on all players and add theit name to strings list
    for (const Player* p : this->list)
        pList[i++] = p->getName();
        
    return pList;
}

PlayersList::iterator::iterator(vector<Player *>::iterator current):
    current(current)
{
    // If iterator points to begin of list, and the first player is the current turn player
    // so go to next player
    if (this->current == PlayersList::getInstance().list.begin() &&
        *this->current == PlayersList::getInstance().current())
            ++this->current;
}

PlayersList::iterator& PlayersList::iterator::operator++() 
{
    auto next = ++current;

    // If this is not last player and this is the current turn player
    // so skip to next player
    if (next != PlayersList::getInstance().list.end() && 
        *next == PlayersList::getInstance().current())
        ++current;

    return *this;
}

const PlayersList::iterator PlayersList::iterator::operator++(int) 
{
    // Creates copy of this iterator
    iterator tmp = *this;

    // Forward iterator
    ++*this;

    // Return copy
    return tmp;
}