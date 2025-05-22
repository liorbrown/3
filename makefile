CXX=g++
CXXFLAGS=-std=c++2a -g -c

.PHONY: clean Main valgrind build

Main: buildMain
	./main.out

valgrind: buildMain
	valgrind --leak-check=yes ./main.out
	valgrind --leak-check=yes ./test.out

buildMain: main.o Baron.o Game.o General.o Governor.o Judge.o Merchant.o Player.o PlayersList.o Spy.o
	$(CXX) $^ -o main.out

main.o: main.cpp Game.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

Baron.o: Baron.cpp Baron.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

Game.o: Game.cpp Game.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

General.o: General.cpp General.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

Governor.o: Governor.cpp Governor.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

Judge.o: Judge.cpp Judge.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

Merchant.o: Merchant.cpp Merchant.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

Player.o: Player.cpp Player.hpp Game.hpp PlayersList.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

PlayersList.o: PlayersList.cpp PlayersList.hpp Game.hpp Baron.hpp General.hpp Governor.hpp Judge.hpp Merchant.hpp Player.hpp Spy.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

Spy.o: Spy.cpp Spy.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o *.out