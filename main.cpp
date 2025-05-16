#include "Game.hpp"
#include <iostream>

using namespace std;

int main()
{
    cout << "🚀🚀🚀🚀🚀🚀🚀 Welcome to coup! 🚀🚀🚀🚀🚀🚀🚀" << endl;

    Game newGame;

    newGame.start();

    char* winner = newGame.winner();

    if (winner)
        cout << "The winner is 🥁🥁🥁🥁🥁🥁: " << winner << endl;
    
    cout << "Bye Bye 🤗";
}