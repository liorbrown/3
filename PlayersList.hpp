// liorbrown@outlook.co.il

#pragma once

// This flag is use for define code that is relevante only for testing the code
// Will be erase before upload to prod 
#define TEST_MODE

#include <vector>
#include <string>
#include "Player.hpp"

using namespace std;

/// @brief This is singltone container of all players in the game
class PlayersList
{
    private:
        static PlayersList* instance;

        size_t turn;

        // List contain pointers and not objects for prevent slicing of derived classes
        vector<Player*> list;
        vector<Player*>::iterator turnsIterator;

        /// @brief Private constructor implement singleton DP
        PlayersList(){}

        // In singleton the right way to implement rule of three is by aborting copy functions
        // instead of implement them
        PlayersList(const PlayersList&) = delete;
        PlayersList& operator=(const PlayersList&) = delete;

        /// @brief Destructor delete all players in list
        ~PlayersList(){this->clear();}        
        
    public:
        static PlayersList& getInstance();

        /// @brief Call instance destructor
        static void free();

        size_t getTurn() const {return this->turn;}

        /// @brief Forward game to next turn
        /// @return Player of new turn
        Player* getNext();

        /// @brief Creates string that represent players list
        /// @return Generated string
        string getListString();

        /// @brief Get player by name
        /// @param name Name of wanted player
        /// @return Pointer to wanted player, null if not found
        Player* getPlayer(const string& name) const;

        /// @brief Creates new player and pick it roll randomly
        /// @param name New player name
        /// @return True - if succeed, false - otherwise
        bool newPlayer(string name);
        
        /// @brief Gets player of current turn
        /// @return Pointer to this turn player. null if empty
        Player* current();
        
        /// @brief Remove given player from list
        /// @param player Pointer to the player to remove
        void remove(Player* player);

        /// @brief Clear players list, and free objects memory
        void clear();

        /// @brief This method return list of all players name
        /// This method was only written because we were explicitly asked to implement it in the instructions. 
        /// In practice, I did not find any logical use for it in the game, so it was not used anywhere.
        /// @return Array of strings of players name
        vector<string> players() const;

        /// @brief This is the container iterator
        /// Its run on all players exclude current player turn
        /// This is hanful in the implementation of the game 
        /// e.g. loop players for ask blocking action, or for present other players
        /// for make action on them
        class iterator
        {
            private:
		        vector<Player*>::iterator current;
	        
            public:
                iterator(vector<Player*>::iterator current);

                // Usualy -> return pointer and * return object itself
                // but here i return unusually pointer for *  like -> 
                // because foreach uses * and i want to prevent object slicing
                // so i use only pointers
                Player* operator*() const {return *current;}
                Player* operator->() const {return *current;}

                /// @brief Prefix increasment
                /// @return This iterator
                iterator& operator++();

                /// @brief Postfix increasment
                /// Usually iterators are passed by value and not by const& as they are small.
                /// @param  Dummy param for tell this is postfix
                /// @return Copy of iterator before increasment
                const iterator operator++(int);

                bool operator==(const iterator& rhs) const {return current == rhs.current;}

                bool operator!=(const iterator& rhs) const {return !(*this == rhs);}
        };       

        iterator begin(){return this->list.begin();}
        iterator end() {return this->list.end();}

        #ifdef TEST_MODE
        /// @brief Because the insertion is randomise, we create this method for testing
        /// our desire players list
        /// @param newPlayer New player that created outside method
        friend void emplaceBack(PlayersList& list, Player* newPlayer);
        #endif
};
