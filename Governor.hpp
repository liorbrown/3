// liorbrown@outlook.co.il
#pragma once

#include "Player.hpp"

class Governor : public Player
{
    private:
        bool tax();
        bool blockTax();

    public:
        Governor(string name): Player(name){} 
};