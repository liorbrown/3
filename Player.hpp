// liorbrown@outlook.co.il

#pragma once

#include <cstddef>
#include <string>
#include <iostream>

using namespace std;

/// @brief This is base class for all players
/// Can't create instance of this class because constructor is protected
/// but its not oficial abstract because have no pure virtual method
class Player
{
    private:
        string name; 
        size_t coins;
        bool isSanctioned;
        bool isBribe;
        size_t arrestedTurn;
        bool isBlockArrest;
        
    protected:
        
        /// @brief Protected constructor for use of derived classes
        /// @param name Player name
        Player(string name):
            name(name), 
            coins(0),
            isBlockArrest(false),
            isSanctioned(false), 
            isBribe(false), 
            arrestedTurn(0),
            ability(NONE){}

        /// @brief This method called when other player do sanction on this player
        /// in the regular version its only sets isSanctioned to true
        /// whats block him from doing gather or tax in his next turn
        virtual void sanctioned(){this->isSanctioned = true;}

    public:

        /// @brief This enams contains only special abilities that can't be implemented whole in
        /// derived class itself, because action depends on user interface
        /// so derived class only hints with this flag what it can do
        /// and the interface use this hint for know what to do with object.
        /// This is alternative of use "if typeid(*Player)==[]" witch considered bad practice
        enum specialAbility
        {
            NONE,
            BLOCK_TAX,
            BLOCK_BRIBE,
            BLOCK_COUP,
            EXCHANGE,
            SPYING
        };

        /// @brief Increase coins by one where merchant have at least 3 coins
        /// do nothing for others
        virtual void increaseCoins(){}

        /// @brief Increase player coins by 1
        void gather(){++*this;}

        /// @brief Increase player coins by 2
        virtual void tax(){this->coins += 2;}

        /// @brief Gives player play 2 turns arow
        /// can't be played 2 turns arow
        void bribe();

        /// @brief Prevent other player from play gather or tax in his next turn
        /// @param Selected Player to do sanction on him
        void sanction(Player* selected);

        /// @brief Elimination other player from the game
        /// @param selected Selected Player to eliminate from the game
        void coup(Player* selected);

        /// @brief Called when other player arrest this player, 
        /// makes him lose give coin to thoer player
        /// @return True - if arrest success, false - otherwise
        virtual bool arrested();
        
        // Getters and setters
        string getName() const {return this->name;}
        size_t getCoins() const {return this->coins;}
        size_t& getCoins() {return this->coins;}
        specialAbility getAbility() const {return this->ability;}
        bool getIsSanctioned() const {return this->isSanctioned;}
        bool& getIsSanctioned() {return this->isSanctioned;}
        bool getIsBribe() {return this->isBribe;}
        bool getIsBlockArrest() const {return this->isBlockArrest;}
        bool& getIsBlockArrest(){return this->isBlockArrest;}
        size_t getArrestedTurn() const {return this->arrestedTurn;}

        /// @brief Sets isBribe to false after first bribed turn
        void Unbribe() {this->isBribe = false;}

        /// @brief If have coins, deacrese them by 1
        /// Implement only prefix because not need postfix in the game
        /// @return This player after decreasing
        Player& operator--();

        /// @brief Increase player coins by 1
        /// Implement only prefix because not need postfix in the game
        /// @return This player after increasing
        Player& operator++();

    protected:
        specialAbility ability;
};