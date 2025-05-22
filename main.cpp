// liorbrown@outlook.co.il

#include "Game.hpp"
#include <iostream>

using namespace std;

int main()
{
    Game::free();
    PlayersList::free();

    cout << "🚀🚀🚀🚀🚀🚀 Welcome to coup! 🚀🚀🚀🚀🚀🚀" << endl;

    Game::getIstance().start();

    string winner = Game::getIstance().winner();

    if (winner.empty())
        cout << "The winner is 🥁🥁🥁🥁🥁🥁: " << winner << endl;
    
    cout << "Bye Bye 🤗" << endl;

    Game::free();
    PlayersList::free();
}