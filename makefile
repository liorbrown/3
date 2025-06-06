CXX=g++
CXXFLAGS=-std=c++2a -g -c
SFMLFLAGS=-lsfml-system -lsfml-window -lsfml-graphics

.PHONY: clean Main test valgrind buildMain

Main: buildMain
	./main.out

test: buildTest
	./test.out

valgrind: buildMain buildTest
	valgrind --leak-check=yes ./main.out
	valgrind --leak-check=yes ./test.out

buildMain: main.o Baron.o Game.o General.o Judge.o Player.o PlayersList.o Merchant.o Button.o
	$(CXX) $^ -o main.out $(SFMLFLAGS)

buildTest: CoupTest.o Baron.o Game.o General.o Judge.o Player.o PlayersList.o Merchant.o Button.o
	$(CXX) $^ -o test.out $(SFMLFLAGS)

CoupTest.o: CoupTest.cpp PlayersList.hpp Baron.hpp General.hpp Governor.hpp Judge.hpp Merchant.hpp Player.hpp Spy.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

Button.o: Button.cpp Button.hpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(SFMLFLAGS)

main.o: main.cpp Game.hpp Player.hpp Button.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

Game.o: Game.cpp Game.hpp Player.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

Player.o: Player.cpp Player.hpp Game.hpp PlayersList.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

PlayersList.o: PlayersList.cpp PlayersList.hpp Game.hpp Baron.hpp General.hpp Governor.hpp Judge.hpp Merchant.hpp Player.hpp Spy.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

Baron.o: Baron.cpp Baron.hpp Player.hpp Game.hpp PlayersList.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

General.o: General.cpp General.hpp Player.hpp Game.hpp PlayersList.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

Judge.o: Judge.cpp Judge.hpp Player.hpp Game.hpp PlayersList.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

Merchant.o: Merchant.cpp Merchant.hpp Player.hpp Game.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o *.out