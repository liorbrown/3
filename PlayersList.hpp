// liorbrown@outlook.co.il
#pragma once

#include <map>
#include "General.hpp"
#include "Governor.hpp"
#include "Judge.hpp"
#include "Merchant.hpp"
#include "Spy.hpp"
#include "Baron.hpp"
#include <string>

using namespace std;

class PlayersList
{
    private:
        static PlayersList* instance;

        PlayersList();
        map<string, Player> list;

    public:
        static PlayersList& getInstance();

        Player* getNext() const;
        Player* getPlayer(const string& name) const;
        string* players() const;
        void turn() const;
        void free();

        class cycleIterator
        {
            private:
		        Player* current;

	        public:

                cycleIterator(Player* ptr = nullptr):current(ptr) {}

                Player& operator*() const {return *current;}

                Player* operator->() const {return current;}

                // ++i;
                cycleIterator& operator++();

                // i++;
                // Usually iterators are passed by value and not by const& as they are small.
                const cycleIterator operator++(int) {
                    cycleIterator tmp = *this;
                    ++*this;
                    return tmp;
                }

                bool operator==(const cycleIterator& rhs) const {return current == rhs.current;}

                bool operator!=(const cycleIterator& rhs) const {return !(*this == rhs);}
        };

        class blockIterator
        {
            private:
		        Player* current;

	        public:

                blockIterator(Player* ptr = nullptr):current(ptr) {}

                Player& operator*() const {return *current;}

                Player* operator->() const {return current;}

                // ++i;
                blockIterator& operator++();

                // i++;
                // Usually iterators are passed by value and not by const& as they are small.
                const blockIterator operator++(int) {
                    blockIterator tmp = *this;
                    ++*this;
                    return tmp;
                }

                bool operator==(const blockIterator& rhs) const {return current == rhs.current;}

                bool operator!=(const blockIterator& rhs) const {return !(*this == rhs);}
        };

        cycleIterator begin() {return {&(*list.begin()).second};}
        cycleIterator end() {return {};}

        blockIterator bBegin() {return {&(*list.begin()).second};}
        blockIterator bEnd() {return {};}
};
