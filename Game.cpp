// liorbrown@outlook.co.il

#include "Game.hpp"
#include "Player.hpp"

Game* Game::instance = nullptr;

Game &Game::getIstance()
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
    for 
    (
        auto turnsIterator = PlayersList::getInstance().begin();
        *turnsIterator != PlayersList::getInstance().end();
        ++*turnsIterator
    ) 
    {
        ++this->turnNum;
        this->turnName = (*turnsIterator)->getName();
        
        (*turnsIterator)->playTurn();
    }
    
    this->winnerName = PlayersList::getInstance().getWinner().getName();

    cout << "And the winner is 🥁🥁🥁🥁🥁🥁🥁🥁:\n" << this->winner() << endl;
}