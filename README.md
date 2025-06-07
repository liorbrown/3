I did this project as part of my undergraduate studies in Software Engineering at Ariel University in the C++ course.
In this project, we were asked to implement a reduced version of the COUP box game. [This](https://github.com/BenjaminSaldman/CPP_EX3_25) is a link to the instructions for the assignment detailing the way we were asked to implement the game.

**Instructions:**

Because the instructions were not detailed to the end and left us room to engineer the game a little ourselves, I will list here a few points regarding the rules of the game as I implemented them:
1) The game is played in turns, but if a player in his turn performs an action that can be blocked by other players, then before the turn continues, the game immediately turns to each of the players who can block the action and asks them whether they want to block it, and therefore all blockings are performed "in real time"
2) A player cannot bribe twice in a row, meaning that once he has bribed, he must play another action, and only in his additional action he allowed to bribe again if he wishes
3) If a player arrests another player and the other player has no coins, then nothing happens and the player loses his turn
4) It is not possible to arrest 2 turns in a row on the same player, this means that only in the turn following the turn in which the arrest was made, he cannot be arrested again, but in the turn after him, he can be arrested again, even though his turn has not even come once
5) If an arrest action is performed on a merchant and he only has one coin, then the operator does not receive a coin, and the merchant loses only one coin
6) If a player performs a sanction on a judge and he only has 3 coins, then the action is successful even though he loses only 3 coins instead of 4

**Classes:**

The code is divided into the following classes:
1) Player - This is the base class that represents all the players in the game. It contains all the relevant information about the player and all the actions he can perform. The class is virtual but not pure virtual, because it does not contain any pure virtual methods. Nevertheless, the class constructor is not public so that it is not possible to create an object of the class, this is because each player must have a specific role, and therefore only a player with a specific role can be created, these are the classes that inherit from the base class of Player.
2) The role classes - Judge, Spy, General, Governor, Baron and Merchant. These classes inherit from the base class Player and each of them implements virtual methods that override the methods of the base class, according to the unique characteristics of each role.
The principle of virtuel inhereit here is so strong that the game class even not include thoses classes at all, and its know only the player base class
4) The player list - This is a container that contains the player list. The container provides basic operations in managing the player list such as: adding a new player, deleting a player, returning a player by name, etc. In addition, it is responsible for managing the turns by each time holding a pointer to the player whose turn it is and the turn number, and it transfers the turns between the players.
This class also contains a standard iterator that allows you to traverse all players except the player whose turn it is. This iterator is useful for many operations such as traversing all players who can block a certain action, or to display a list of all other players for a player who wants to perform a certain action on another player.
This class is a singleton because at any given moment there can only be one list of players. When you want to perform another game, you clear the list of players and refill it.
5) Game - This class generates the user interface using the SFML library, and manages the entire course of the game using the previously mentioned classes. This class is also a singleton because at any given moment only one game is running.
6) Button - This class implements a button object using the SFML library. The main advantage of using this class, unlike the simple rectangle provided by the library, is the possibility of activating the button according to the game conditions, and checking whether the button was pressed, depending on the cursor position at the time of pressing and whether it is activated or not.
   
**Additional files:**

1) main.cpp - This file is quite sparse and its purpose is only to run the game and release the dynamic memory resources at the end of the program
2) CoupTest.cpp - A file containing unit tests for all classes, except the user interface classes
3) makefile - This file allows you to compile the game and run it, as well as compile and run the test file. In addition, it allows you to run a valgrind test on the program itself and on the tests, as well as the option to clean all binary files.
4) Roboto-MediumItalic.ttf - This file contain the font that uses in the GUI
 
**Additional methods:**

In addition to the game itself, I implemented 3 more methods in the code that we were asked to implement in the assignment instructions. In practice, I did not find a logical use for them within the game itself, so they are only implemented according to the instructions but are not actually used:
1) turn
2) winner
3) players
   
**Code design considerations:**

The guiding principle I based this program on is the principle of modularity. It was important to me to completely separate the logical part of the objects present in the game and the relationships between them, from the user interface.
This separation allows you to take all the code of the logical classes and use it in any other user interface that a person chooses, such as running in a terminal, on a browser, etc. 
The practical expression of this modularity is that all the logical classes do not even know the game class or the SFML library, and thus they are completely disconnected from the interface.

It is important to note that this modularity comes at the expense of the fact that much of the actual logic had to be implemented only in the game class and not in the player and role classes, because in this game there are many interactions with the user. For example, in the spying action, the user must first be asked if he wants to spy, then asked who he wants to spy on, and after showing him the amount of coins the player has, he is asked again if he wants to prevent him from making an arrest. Because the Spy class does not know the user interface, it turns out that in practice this entire process is implemented in the game class, while in the spy class all that is left is just a flag that says it can spy.

This created a situation where the role classes are very, very sparse to the point that I wondered whether it even makes sense to use inheritance here, and instead it would be better to settle for an ENUM that each player would hold and for me the actions would be performed in the user interface.

In practice, the main reason I decided to keep the inheritance model is for pedagogical reasons, as the instructions explicitly stated that the expectation was that in this assignment we would practice the inheritance principle we learned about in class, so in order to practice this principle I decided to do inheritance, but if I were required to implement this game regardless of the course, it might have been more appropriate not to use inheritance at all, because the inheriting classes actually remained almost without their own content.

**Additional notes:**

1) The unit test file contains tests only on the logical classes and not on the user interface.
2) Running valgrind shows many memory leaks, but all the memory leaks originate only from the use of the SFML library and the resulting memory leaks related to the operating system's graphics card. It can be seen that running the VALGRIND test on the unit test file does not have any memory leaks at all, because there is no reference to the user interface.
3) I wrote all 2345 code lines of this assignment myself without any consultation or any other use of AI tools, in order to learn as much as possible about myself while carrying out the assignment in the most effective way.
