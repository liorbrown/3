CXX=g++
CXXFLAGS=-std=c++2a -g -c
SFMLFLAGS=-lsfml-system -lsfml-window -lsfml-graphics
BUTTONLIB= -L. -lSFMLButton 

.PHONY: clean Main valgrind build

Main: buildMain
	./main.out

valgrind: buildMain
	valgrind --leak-check=yes ./main.out

buildMain: main.o Baron.o Game.o General.o Judge.o Player.o PlayersList.o Merchant.o Button.o
	$(CXX) $^ -o main.out $(SFMLFLAGS) $(BUTTONLIB)

Button.o: Button.cpp Button.hpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(SFMLFLAGS)

main.o: main.cpp Game.hpp Player.hpp Button.hpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(SFMLFLAGS)

Game.o: Game.cpp Game.hpp Player.hpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(SFMLFLAGS)

Player.o: Player.cpp Player.hpp Game.hpp PlayersList.hpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(SFMLFLAGS)

PlayersList.o: PlayersList.cpp PlayersList.hpp Game.hpp Baron.hpp General.hpp Governor.hpp Judge.hpp Merchant.hpp Player.hpp Spy.hpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(SFMLFLAGS)

Baron.o: Baron.cpp Baron.hpp Player.hpp Game.hpp PlayersList.hpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(SFMLFLAGS)

General.o: General.cpp General.hpp Player.hpp Game.hpp PlayersList.hpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(SFMLFLAGS)

Judge.o: Judge.cpp Judge.hpp Player.hpp Game.hpp PlayersList.hpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(SFMLFLAGS)

Merchant.o: Merchant.cpp Merchant.hpp Player.hpp Game.hpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(SFMLFLAGS)

clean:
	rm *.o *.out