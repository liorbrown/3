// liorbrown@outlook.co.il
#pragma once

#include <map>
#include <string>
#include "Player.hpp"

using namespace std;

class PlayersList
{
    private:
        static PlayersList* instance;

        map<string, Player*> list;

        ~PlayersList(){this->clear();}
        
        Player* createPlayer(string name);
        void clear();

    public:
        static PlayersList& getInstance();
        static void free();

        const char* getWinner() const {return this->list.begin()->first.c_str();}
        void init();
        Player* getPlayer(const string& name) const;
        string* players() const;
        void turn() const {}
        void remove(Player* player);

        class cycleIterator
        {
            private:
		        map<string, Player*>::iterator current;

	        public:

                cycleIterator(map<string, Player*>::iterator ptr):current(ptr) {}

                Player& operator*() const {return *current->second;}
                Player* operator->() const {return current->second;}

                // ++i;
                cycleIterator& operator++();

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
		        map<string, Player*>::iterator current;

	        public:

                peersIterator(map<string, Player*>::iterator ptr, const string currentPlayer):
                    current(ptr), currentPlayer(currentPlayer) {}

                Player& operator*() const {return *current->second;}
                Player* operator->() const {return current->second;}

                // ++i;
                peersIterator& operator++();

                // i++;
                // Usually iterators are passed by value and not by const& as they are small.
                const peersIterator operator++(int);

                bool operator==(const peersIterator& rhs) const {return current == rhs.current;}

                bool operator!=(const peersIterator& rhs) const {return !(*this == rhs);}
        };

    cycleIterator begin();
    cycleIterator end() {return{{}};}

    peersIterator pBegin(string currentPlayer);
    peersIterator pEnd() {return {this->list.end(),{}};}        
};
