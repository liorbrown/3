// liorbrown@outlook.co.il
#pragma once

#include <cstddef>

class Player
{
    private:
        char* name;
        size_t coins;
        bool isSanctioned;
        Player();

    public:
        void playTurn();
        void gather();
        void tax();
        void bribe();
        void arrest();
        void sanction();
        void coup();
};