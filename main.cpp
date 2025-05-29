// liorbrown@outlook.co.il

#include "Game.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

void testSMFL()
{
    RenderWindow window(VideoMode({200, 200}), "SFML works!");
    CircleShape shape(100.f);
    shape.setFillColor(Color::Green);

    while (window.isOpen())
    {
        Event event;
        window.pollEvent(event);

        if (event.type == Event::EventType::Closed)
            window.close();

        window.clear();
        window.draw(shape);
        window.display();
    }
}

int main()
{
    //testSMFL();
    cout << "🚀🚀🚀🚀🚀🚀 Welcome to coup! 🚀🚀🚀🚀🚀🚀" << endl;

    Game::getIstance().start();

    string winner = Game::getIstance().winner();

    if (!winner.empty())
        cout << "The winner is 🥁🥁🥁🥁🥁🥁: " << winner << endl;
    
    cout << "Bye Bye 🤗" << endl;

    Game::free();
    PlayersList::free();
}