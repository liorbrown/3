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
        
        bool isSanctioned;
        bool isBribe;
        size_t arrestedTurn;

        void gather();  
        void bribe();
        void arrest();
        void sanction();
        void coup();
            
        virtual bool blockTax(){return false;}
        virtual bool blockCoup(){return false;}
        virtual bool blockBribe(){return false;}
        virtual void specialAction(){}
        virtual void arrested();

    protected:
        size_t coins;
        bool blockArrest;

        Player(string name):
            name(name), 
            coins(0),
            blockArrest(false),
            isSanctioned(false), 
            isBribe(false), 
            arrestedTurn(0){}

        virtual bool tax();
        virtual void sanctioned(){this->isSanctioned = true;}
        Player* choosePlayer();

    public:
        string getName() const {return this->name;}
        const bool getIsBribe() const {return this->isBribe;}
        void Unbribe() {this->isBribe = false;}
        void arrestBlocking() {this->blockArrest = true;}
        virtual void playTurn();

        Player& operator--();
        Player& operator++();
};