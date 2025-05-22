// liorbrown@outlook.co.il
#pragma once

#include <cstddef>
#include <string>

using namespace std;

class Player
{
    private:
        string name;
        size_t coins;
        bool isSanctioned;
        bool isBribe;
        size_t arrestedTurn;

        void gather();
        void tax();
        void bribe();
        void arrest();
        void sanction();
        void coup();

        Player* choosePlayer();

    protected:
        Player(string name):
            name(name), 
            coins(0), 
            isSanctioned(false), 
            isBribe(false), 
            arrestedTurn(0){}

    public:
        string getName() const {return this->name;}
        const bool getIsBribe() const {return this->isBribe;}
        bool& getIsBribe() {return this->isBribe;}

        virtual void playTurn();
        
};