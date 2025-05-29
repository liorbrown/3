// liorbrown@outlook.co.il

#include "Game.hpp"
#include "Player.hpp"

Game* Game::instance = nullptr;

Game &Game::getInstance()
{
    if (!instance)
        instance = new Game;
    
    return (*instance);
}

void Game::free()
{
    if (instance)
    {
        delete instance;
        instance = nullptr;
    }
}

void Game::start()
{   
    Player* current;

    while (current = PlayersList::getInstance().getNext())
        current->playTurn();
    
    this->winnerName = PlayersList::getInstance().current()->getName();
}

void Game::turn() const
{
    cout << PlayersList::getInstance().current()->getName();
}