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
        vector<Player*>::iterator turnsIterator;

        PlayersList(){}
        PlayersList(const PlayersList&) = delete;
        PlayersList& operator=(const PlayersList&) = delete;
        ~PlayersList(){this->clear();}
        
        Player* createPlayer(string name);
        

    public:
        static PlayersList& getInstance();
        static void free();

        string getListString();
        bool newPlayer(string name);
        Player* getNext();
        Player* current(){return *this->turnsIterator;}
        Player* getPlayer(const string& name) const;
        string* players() const;
        void remove(Player* player);
        void clear();

        class iterator
        {
            private:
		        vector<Player*>::iterator current;
	        
            public:
                iterator(vector<Player*>::iterator current);

                Player* operator*() const {return *current;}
                Player* operator->() const {return *current;}

                // ++i;
                iterator& operator++();

                // i++;
                // Usually iterators are passed by value and not by const& as they are small.
                const iterator operator++(int);

                bool operator==(const iterator& rhs) const {return current == rhs.current;}

                bool operator!=(const iterator& rhs) const {return !(*this == rhs);}
        };       

        iterator begin(){return this->list.begin();}
        iterator end() {return this->list.end();}
};
