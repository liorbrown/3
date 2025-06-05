// liorbrown@outlook.co.il

#pragma once

#include <string>
#include <iostream>
#include "PlayersList.hpp"
#include "Button.hpp"

using namespace std;
using namespace sf;


class Game
{
    private:

        enum actionType
        {
            ARREST,
            SANCTION,
            OTHER
        };

        static Game* instance;

        RenderWindow window;
        Font font;
        size_t turnNum;
        string winnerName;

        Game():window(VideoMode(800, 800), "Coup"), turnNum(0)
            {font.loadFromFile("Roboto-MediumItalic.ttf");}
        
        void openStartWindow();
        void openPlayersInitWindow();
        void openTurnsWindow();
        void openFinishWindow();
        bool openDecisionWindow(string label);
        Player* openPlayerPicker(string label, actionType action = OTHER);
        void arrestedFailed();

        bool gather(Player* current);
        bool tax(Player* current);
        bool bribe(Player* current);
        bool arrest(Player* current);
        bool sanction(Player* current);
        bool coup(Player* current);
        void exchange(Player* current);
        void spying(Player* current);

        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;
        
    public:
        
        static Game& getInstance();
        static void free();
        
        void start(){this->openStartWindow();}
        const Font& getFont() const {return this->font;}
        size_t getTurnNum() const {return this->turnNum;}
        string winner() const {return this->winnerName;}
        void turn() const; 
};