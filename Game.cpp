// liorbrown@outlook.co.il

#include "Game.hpp"

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
    PlayersList::getInstance().init();
    
    for (Player& p: PlayersList::getInstance())
    {
        ++this->turnNum;
        this->turnName = p.getName();

        p.playTurn();
    }

    this->winnerName = PlayersList::getInstance().begin()->getName();

    cout << "And the winner is 🥁🥁🥁🥁🥁🥁🥁🥁🥁:\n" << this->winner() << endl;
}