// liorbrown@outlook.co.il
#pragma once

#include <vector>
#include <string>

using namespace std;

class Player;

class PlayersList
{
    private:
        static PlayersList* instance;

        vector<Player*> list;        
        PlayersList():iterator({}){}

        PlayersList(const PlayersList&) = delete;
        PlayersList& operator=(const PlayersList&) = delete;
        ~PlayersList(){this->clear();}
        
        Player* createPlayer(string name);
        void clear();

    public:
        static PlayersList& getInstance();
        static void free();

        
        Player* getPlayer(const string& name) const;
        string* players() const;
        void turn() const {}
        void remove(Player* player);
        Player& getWinner(){return *this->list.at(0);}

        class cycleIterator
        {
            private:
		        vector<Player*>::iterator current;

	        public:

                cycleIterator(vector<Player*>::iterator ptr):current(ptr) {}

                

                Player* operator*() const {return *current;}
                Player* operator->() const {return *current;}

                // ++i;
                cycleIterator* operator++();

                // i++;
                // Usually iterators are passed by value and not by const& as they are small.
                const cycleIterator operator++(int);

                bool operator==(const cycleIterator& rhs) const {return current == rhs.current;}

                bool operator!=(const cycleIterator& rhs) const {return !(*this == rhs);}
        };

        class peersIterator
        {
            private:
                string currentPlayer;
		        vector<Player*>::iterator current;

	        public:

                peersIterator(vector<Player*>::iterator ptr, const string currentPlayer):
                    current(ptr), currentPlayer(currentPlayer) {}

                Player& operator*() const {return **current;}
                Player* operator->() const {return *current;}

                // ++i;
                peersIterator& operator++();

                // i++;
                // Usually iterators are passed by value and not by const& as they are small.
                const peersIterator operator++(int);

                bool operator==(const peersIterator& rhs) const {return current == rhs.current;}

                bool operator!=(const peersIterator& rhs) const {return !(*this == rhs);}
        };

    cycleIterator iterator;
    Player* current(){return *this->iterator;}
    
    cycleIterator* begin();
    cycleIterator end() {return{{}};}

    peersIterator pBegin(string currentPlayer);
    peersIterator pEnd() {return {this->list.end(),{}};}        
};
