// liorbrown@outlook.co.il

#pragma once

#include <string>
#include <iostream>
#include "PlayersList.hpp"
#include "Button.hpp"

using namespace std;
using namespace sf;

/// @brief This singleton class handle all the GUI that runs the game
class Game
{
    private:

        /// @brief This action type ךists only the actions required 
        /// to activate the buttons in the player selection menu
        enum actionType
        {
            ARREST,
            SANCTION,
            OTHER
        };

        static Game* instance;

        RenderWindow window;
        Font font;
        string winnerName;

        /// @brief Private game constructor, creates the main window and load the font
        Game():window(VideoMode(800, 800), "Coup")
            {font.loadFromFile("Roboto-MediumItalic.ttf");}
        
        /// @brief Opens the start window
        void openStartWindow();

        /// @brief Open the window of init players list
        void openPlayersInitWindow();

        /// @brief Open the main window of the game itself
        void openTurnsWindow();

        /// @brief Open window of finishing the game
        void openFinishWindow();

        /// @brief Open decision window for ask player yes or no qustion 
        /// @param label The qustion to ask the user
        /// @return True - if clicked yes, false - otherwise
        bool openDecisionWindow(string label);

        /// @brief Open window that gives the player option to pick one of other players
        /// @param label The qustion to ask the user
        /// @param action The type of action to do on choosen player
        /// @return Selected player or null if not selected
        Player* openPlayerPicker(string label, actionType action = OTHER);

        /// @brief Open window that inform player that arrest action failed
        void arrestedFailed();

        /// @brief Gain 1 coin
        /// @param current Current turn player
        /// @return True - if turns end, false - otherwise
        bool gather(Player* current);

        /// @brief Gain 2 coin
        /// @param current Current turn player
        /// @return True - if turns end, false - otherwise
        bool tax(Player* current);

        /// @brief Gets extra turn
        /// @param current Current turn player
        /// @return True - if turns end, false - otherwise
        bool bribe(Player* current);

        /// @brief Take 1 coin from other player
        /// @param current Current turn player
        /// @return True - if turns end, false - otherwise
        bool arrest(Player* current);

        /// @brief Prevent other player from do gather or tax
        /// @param current Current turn player
        /// @return True - if turns end, false - otherwise
        bool sanction(Player* current);

        /// @brief Eliminate other player from game
        /// @param current Current turn player
        /// @return True - if turns end, false - otherwise
        bool coup(Player* current);

        /// @brief Exchange 3 coins for 6
        /// @param current Current turn player
        void exchange(Player* current);

        /// @brief See other player coins, and prevent him from arresting
        /// @param current Current turn player
        void spying(Player* current);

        // In singleton the right way to implement rule of three is by aborting copy functions
        // instead of implement them
        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;
        
    public:
        
        static Game& getInstance();
        static void free();
        
        // Geters
        const Font& getFont() const {return this->font;}

        /// @brief This method return winner name
        /// This method was only written because we were explicitly asked to implement it in the instructions. 
        /// In practice, I did not find any logical use for it in the game, so it was not used anywhere.
        /// @return Winner name. if game not ended return empty string
        string winner() const;

        /// @brief Starts new game
        void start(){this->openStartWindow();}

        /// @brief This method print current turn player name
        /// This method was only written because we were explicitly asked to implement it in the instructions. 
        /// The instruction says to "print" the name and not to return it, and its was not clearly where to print
        /// so I print it to console, קven though the game runs on GUI
        /// In practice, I did not find any logical use for it in the game, so it was not used anywhere.
        void turn() const; 
};