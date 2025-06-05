// liorbrown@outlook.co.il

#include "Game.hpp"

int main()
{
    Game::getInstance().start();
    
    Game::free();
    PlayersList::free();
}