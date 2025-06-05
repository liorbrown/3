// liorbrown@outlook.co.il

#pragma once

#include <cstddef>
#include <string>
#include <iostream>
#include "Game.hpp"

using namespace std;

class Player
{
    private:
        string name; 
        size_t coins;
        bool isSanctioned;
        bool isBribe;
        size_t arrestedTurn;
        bool isBlockArrest;
        
    protected:
        
        Player(string name):
            name(name), 
            coins(0),
            isBlockArrest(false),
            isSanctioned(false), 
            isBribe(false), 
            arrestedTurn(0),
            ability(NONE){}

        virtual void sanctioned(){this->isSanctioned = true;}

    public:

        enum specialAbility
        {
            NONE,
            BLOCK_TAX,
            BLOCK_BRIBE,
            BLOCK_COUP,
            EXCHANGE,
            SPYING
        };

        virtual void increaseCoins(){}
        void gather(){++*this;}
        virtual void tax(){this->coins += 2;}
        void bribe();
        void sanction(Player* selected);
        void coup(Player* selected);
        virtual bool arrested();
        
        string getName() const {return this->name;}
        size_t getCoins() const {return this->coins;}
        size_t& getCoins() {return this->coins;}
        specialAbility getAbility() const {return this->ability;}
        bool& getIsSanctioned() {return this->isSanctioned;}
        bool getIsBribe() const {return this->isBribe;}
        bool& getIsBlockArrest(){return this->isBlockArrest;}
        size_t getArrestedTurn() const {return this->arrestedTurn;}
        void Unbribe() {this->isBribe = false;}

        Player& operator--();
        Player& operator++();

    protected:
        specialAbility ability;
};