// liorbrown@outlook.co.il

#include <sstream>
#include <vector>
#include "Game.hpp"

// Init static singlton pointer to null
Game* Game::instance = nullptr;

Game &Game::getInstance()
{
    if (!instance)
        instance = new Game;
    
    return (*instance);
}

void Game::free()
{
    // If instance created, delete it
    if (instance)
    {
        delete instance;
        instance = nullptr;
    }
}

void Game::openStartWindow()
{
    // Create title
    Text title{"Welcome to coup!", this->font};

    title.setColor(Color::Black);
    title.setPosition({115.f, 50.f});
    title.setScale({2.f,2.f});

    // Create start button
    Button start{{300.f, 270.f},"New Game", this->window};

    // Runs until window closed
    while (this->window.isOpen())
    {
        Event event;

        // Runs on all events that provoke by user
        while (this->window.pollEvent(event))
        {
            // If user close the window, close it
            if (event.type == Event::EventType::Closed)
                this->window.close();
            // If user clicked the start button, start the game
            else if (event.type == Event::EventType::MouseButtonPressed && start.isClicked(event))
                this->openPlayersInitWindow();

            // Clear window and draw it again after each event handle
            this->window.clear(Color::Cyan);
            this->window.draw(title);
            start.draw();
            this->window.display();
        }
    }
}

void Game::openPlayersInitWindow()
{
    string playerInput;

    // Create title
    Text title{"Insert player 1 name:",this->font};
    title.setPosition({270.f, 80.f});
    title.setFillColor(Color::Black);

    // Create player name textbox
    RectangleShape rect{{300.f, 70.f}};
    rect.setPosition({260.f, 180.f});
    rect.setFillColor(Color::White);

    Text input{"",this->font,30};
    input.setPosition({330.f, 195.f});
    input.setColor(Color::Black);

    // Create message text
    Text message{"",this->font,30};
    message.setPosition({315.f, 280.f});
    message.setColor(Color::Red);

    // Create insert new player button
    Button insert{{300.f, 330.f}, "Add Player", this->window, false};

    // Creates players list string
    Text list{"",this->font,30};
    list.setPosition({330.f, 410.f});
    list.setColor(Color::Black);

    // Creates start button
    Button start{{300.f, 650.f}, "Start Game", this->window, false}; 

    size_t nPlayer = 1;

    // Clear players list from data of previous games, if exist
    PlayersList::getInstance().clear();

    // Runs until window closed
    while (this->window.isOpen())
    {
        Event event;

        // Runs on all events that provoke by user
        while (this->window.pollEvent(event))
        {
            // If user close the window, close it
            if (event.type == Event::EventType::Closed)
                this->window.close();

            // If user enter text, update input string and textbox.
            // if title is empty, its indicate that already inserted 6 players
            // and can't insert any more, so dismiss text entering
            else if (event.type == sf::Event::TextEntered && !title.getString().isEmpty())
            {
                // If key preesed is not backspace, add char to input string
                if (event.text.unicode != '\b')
                    playerInput +=event.text.unicode;
                // If backspace hited, and input not empty, erase last char
                else if(!playerInput.empty())
                    playerInput.erase(playerInput.size() - 1, 1);
                
                // Update textbox string
                input.setString(playerInput);

                // Set insert button enable or disable according to if input empty or not
                // because can't create player without name
                insert.getIsEnable() = !playerInput.empty();
            }
            // If user clicked the mouse, check if hit some button
            else if (event.type == Event::EventType::MouseButtonPressed)
            {
                // If user hit insert button
                if (insert.isClicked(event))
                {
                    // Try to create new player, if return false its says that the name already taken
                    // so tells it to user
                    if (!PlayersList::getInstance().newPlayer(playerInput))
                        message.setString("Name already exist");
                    // If player creation successed
                    else
                    {
                        // Clear error message
                        message.setString("");

                        // Clear input string
                        playerInput.clear();

                        // Disable insert button because textbox empty
                        insert.getIsEnable() = false;

                        // Clear textbox
                        input.setString("");

                        // Update players list
                        list.setString(PlayersList::getInstance().getListString());

                        // If this was the 6th player, so remove title and textbox
                        if (nPlayer == 6)
                        {
                            title.setString("");
                            rect.setFillColor(Color::Cyan);
                        }
                        // Regular insertion
                        else
                        {
                            // Increase player counter, and update title
                            title.setString("Insert player " + to_string(++nPlayer) + " name");

                            // If already2 player inserted, enable start button
                            if (nPlayer == 3)
                                start.getIsEnable() = true;
                        }
                    }
                }
                // If user clicked start button, opens main game window
                else if (start.isClicked(event))
                    this->openTurnsWindow();                
            }

            this->window.clear(Color::Cyan);

            // Draw again all elements after event, and refresh window
            this->window.draw(title);
            this->window.draw(rect);
            this->window.draw(message);
            this->window.draw(input);
            insert.draw();
            this->window.draw(list);
            start.draw();

            this->window.display();
        }
    }
}

void Game::openTurnsWindow()
{
    // Creates title
    Text title{"",this->font};
    title.setPosition({270.f, 40.f});
    title.setFillColor(Color::Black);

    // Creates action buttons
    Button gather{{140.f, 160.f}, "Gather", this->window};
    Button tax{{140.f, 260.f}, "Tax", this->window};
    Button bribe{{140.f, 360.f}, "Bribe", this->window};
    Button arrest{{390.f, 160.f}, "Arrest", this->window};
    Button sanction{{390.f, 260.f}, "Sanction", this->window};
    Button coup{{390.f, 360.f}, "Coup", this->window};
    Button skip{{265.f, 460.f}, "Skip", this->window};

    // Creates player list string for show it to user entire game
    Text list{PlayersList::getInstance().getListString(), this->font};
    list.setPosition({250.f, 565.f});
    list.setFillColor(Color::Black);

    Player* current;

    // This is the turns loop, each iteration its get player of next turn
    // until there will remain only 1 player in the game and the getNext return null
    // We also check if the window is open for ensure we exit loop if user want to close the game
    while ((current = PlayersList::getInstance().getNext()) && this->window.isOpen())
    {
        // Increae coins for Merchant only
        current->increaseCoins();

        // Exchange 3 coins by 6 for Baron only
        this->exchange(current);

        // Spying only for Spy
        this->spying(current);
        
        // If player have at least 10 coins, he is must to coup
        if (current->getCoins() >= 10)
        {
            // Make coup
            this->coup(current);

            // Update playerlist string after remove player
            list.setString(PlayersList::getInstance().getListString());
        }
        // If have less then 10 coins, open choose action menu
        else
        {
            bool next = false;

            // Runs until player ends its turn, or close the game
            while (!next && this->window.isOpen())
            {
                // Sets title
                stringstream titleStr;
                titleStr << "     " << current->getName() << 
                        " turn\nyou have " << 
                        current->getCoins() << " coins";
                title.setString(titleStr.str());

                // Disable gather and tax buttons if player sanctioned 
                gather.getIsEnable() = tax.getIsEnable() = !current->getIsSanctioned();

                // Disable bribe button if player already bribed, or if not have enough coins
                bribe.getIsEnable() = current->getCoins() >= 4 && !current->getIsBribe();

                // Disable arrest if spy prevent player from arrest
                arrest.getIsEnable() = !current->getIsBlockArrest();

                // Disable sanction if player donwt have enough coins
                sanction.getIsEnable() = current->getCoins() >= 3;

                // Disable coup if player donwt have enough coins
                coup.getIsEnable() = current->getCoins() >= 7;

                Event event;

                // Runs on all events that provoke by user
                while (this->window.pollEvent(event))
                {
                    // If user click the close button, so close window
                    if (event.type == Event::EventType::Closed)
                        this->window.close();
                    // If user clicked on mouse
                    else if (event.type == Event::EventType::MouseButtonPressed)
                    {
                        // Checks if user clicked one of action buttons, make this action
                        // and gets indication if turn end 
                        if (gather.isClicked(event))
                            next = this->gather(current);
                        else if (tax.isClicked(event))
                            next = this->tax(current);
                        else if (bribe.isClicked(event))
                            next = this->bribe(current);
                        else if (arrest.isClicked(event))
                            next = this->arrest(current);                    
                        else if (sanction.isClicked(event))
                            next = this->sanction(current);
                        else if (coup.isClicked(event))
                        {
                            next = this->coup(current);

                            // Update players list string after eliminate player
                            list.setString(PlayersList::getInstance().getListString());
                        }
                        // This option is crutial because ther are situations where player have no legal action
                        // so we give him the option ti skip for prevent stalemate
                        else if (skip.isClicked(event))
                            next = true;
                    }
                }

                this->window.clear(Color::Cyan);

                // Draw again all elements after event, and refresh window
                this->window.draw(title);
                gather.draw();
                tax.draw();
                bribe.draw();
                arrest.draw();
                sanction.draw();
                coup.draw();
                skip.draw();
                this->window.draw(list);

                this->window.display();
                this->window.requestFocus();
            }

            // Clear isSanction and isBlockArrest because they are only for 1 turn
            current->getIsSanctioned() = current->getIsBlockArrest() = false;
        }
    }

    // After only 1 player remain, Crowning the winner and open finish window
    this->winnerName = PlayersList::getInstance().current()->getName();
    this->openFinishWindow();
}

void Game::openFinishWindow()
{
    // Creates title
    Text title{"And the winner is\n        " + this->winnerName, this->font};

    title.setColor(Color::Black);
    title.setPosition({115.f, 50.f});
    title.setScale({2.f,2.f});

    // Creates start and close buttons
    Button start{{300.f, 270.f},"New Game", this->window};
    Button close{{300.f, 500.f},"Close", this->window};

    // Runs until window closed
    while (this->window.isOpen())
    {
        Event event;

        // Runs on all events that provoke by user
        while (this->window.pollEvent(event))
        {
            // If user click the close button, so close window
            if (event.type == Event::EventType::Closed)
                this->window.close();
            // If user pressed mouse button
            else if (event.type == Event::EventType::MouseButtonPressed)
            {
                // If user clicked start button, start new game
                if (start.isClicked(event))
                    this->openPlayersInitWindow();
                // If user click the close button, so close window
                else if (close.isClicked(event))
                    this->window.close();
            }

            this->window.clear(Color::Cyan);

            // Draw again all elements after event, and refresh window
            this->window.draw(title);
            start.draw();
            close.draw();
            
            this->window.display();
        }
    } 
}

bool Game::openDecisionWindow(string label)
{
    // Creates popup window for make decision
    RenderWindow window{VideoMode(800, 400), "Coup"};
    window.requestFocus();

    // Creates decision title
    Text title{label, this->font};
    title.setColor(Color::Black);
    title.setPosition({140.f, 50.f});

    // Creates yes and no buttons
    Button yes{{120.f,250.f},"Yes", window};
    Button no{{500.f, 250.f},"No", window};

    // Runs until user make a choise
    while (true)
    {
        Event event;

        // Runs on all events that provoke by user
        while (window.pollEvent(event))
        {
            // If user pressed mouse button
            if (event.type == Event::EventType::MouseButtonPressed)
            {
                // Check if user clickes the yes or no button, and update his response
                if (yes.isClicked(event))
                {
                    // Close popup window
                    window.close();

                    return true;
                }
                else if (no.isClicked(event))
                {
                    // Close popup window
                    window.close();

                    return false;
                }
            }

            // Draw again all elements after event, and refresh window
            window.clear(Color::Cyan);
            window.draw(title);
            yes.draw();
            no.draw();
            window.display();
        }
    }
}

Player *Game::openPlayerPicker(string label, actionType action)
{
    // Creates popup window for choose player
    RenderWindow window{VideoMode(800, 750), "Coup"};
    window.requestFocus();

    // Creates title
    Text title{label, this->font};
    title.setColor(Color::Black);
    title.setPosition({140.f, 50.f});

    // Creates vector that contains all other players buttons
    vector<Button> buttons;

    // Sets y coordinate of first button
    float y = 100.f;

    // Runs on all other players
    for (Player* p: PlayersList::getInstance())
    {
        // Sets button to disable if this action is arrest and player arrested in previos turn
        // or if action is sanction and player already sanctioned
        bool enable = !((action == ARREST && 
                        p->getArrestedTurn() &&
                        PlayersList::getInstance().getTurn() - p->getArrestedTurn() == 1) ||
                        action == SANCTION && p->getIsSanctioned());

        // Creates player button and it to buttons vector
        buttons.emplace_back(Button{{330.f, y += 100}, p->getName(), window, enable});
    }

    // Create cancel button
    Button cancel {{330.f, y += 100}, "Cancel", window};

    // Runs until player select other player, or cancel
    while (true)
    {
        Event event;

        // Runs on all events that provoke by user
        while (window.pollEvent(event))
        {
            // Check if mouse button pressed, then check if click cancel button so sets 
            // state to cancel and not check other buttons
            if (event.type == Event::EventType::MouseButtonPressed)
                if (cancel.isClicked(event))
                {
                    // close popup window
                    window.close();
                    return nullptr;
                }
                else
                {
                    // Runs on all players buttons and check if one of them clicked
                    for (const Button& b : buttons)
                        if (b.isClicked(event))
                        {
                            // close popup window
                            window.close();

                            // Gets pointer to player, by his name that on the button
                            return (PlayersList::getInstance().getPlayer(b.getLabel()));
                        }            
                }

            // Draw again all elements after event, and refresh window
            window.clear(Color::Cyan);
            window.draw(title);

            // Runs on all players buttons and draw them
            for (Button& b : buttons)
                b.draw();

            cancel.draw();
            window.display();
            window.requestFocus();
        }
    }
}

void Game::arrestedFailed()
{
    // Creates popup window for choose player
    RenderWindow window{VideoMode(600, 300), "Coup"};
    window.requestFocus();

    // Creates title
    Text title{"Arrested failed, player didn't had coins", this->font};
    title.setColor(Color::Black);
    title.setPosition({60.f, 50.f});

    // Creates close buttom
    Button close{{200.f, 200.f},"OK", window};

    // Runs until window closed
    while (window.isOpen())
    {
        Event event;

        // Runs on all events that provoke by user
        while (window.pollEvent(event))
        {
            // Check if user clicked OK button, close window
            if (event.type == Event::EventType::MouseButtonPressed && close.isClicked(event))
                window.close();

            // Draw again all elements after event, and refresh window
            window.clear(Color::Cyan);
            window.draw(title);
            close.draw();
            window.display();
            window.requestFocus();
        }
    }
}

bool Game::gather(Player* current)
{
    // Gather 1 coin
    current->gather();

    // Indicate turn ends
    return true;
}

bool Game::tax(Player* current)
{
    // Runs on all other players that can block tax, aka governors
    for (Player* p : PlayersList::getInstance())
        if (p->getAbility() == Player::BLOCK_TAX)
        {
            // Sets decision popup title
            stringstream decision;
            decision << "       " << p->getName() << 
            "\ndo you want to block " << current->getName() << " from taxing?";

            // Ask other player if want to block from tax, so block action
            // and user lost it turn
            if (this->openDecisionWindow(decision.str()))
                return true;
        }

    // If no one block him, make tax and gain 2 coins
    current->tax();
    
    // Indicate that turn ends
    return true;
}

bool Game::bribe(Player* current)
{
    // Runs on all other players that can block tax, aka Judges
    for (Player* p : PlayersList::getInstance())
        if (p->getAbility() == Player::BLOCK_BRIBE)
        {
            // Sets popup decision title
            stringstream decision;
            decision << "       " << p->getName() << 
            "\ndo you want to block " << current->getName() << " from bribe?";

            // Ask other player if want to block from bribe, so block action
            // and user lost it turn
            if (this->openDecisionWindow(decision.str()))
                return true;
        }

    // Make bribe
    current->bribe();

    // Indicate that player not finished its turn, because his just got extra
    return false;
}

bool Game::arrest(Player* current)
{
    // Choose other player to arrest, by player picker window
    Player* selected = this->openPlayerPicker("Choose player to arrest", ARREST);

    // If user canceled action, so he not end its turn
    if (!selected)
        return false;
    else
    {
        // Try to arrest selected player
        // If not success because his don't have coins so popup message that arrest failed
        // and he lose its turn
        if (!selected->arrested())
            this->arrestedFailed();

        // Indicate that turn ends
        return true;
    }
}

bool Game::sanction(Player* current)
{
    // Choose other player to sanction, by player picker window
    Player* selected = this->openPlayerPicker("Choose player to sanction", SANCTION);

    // If user canceled action, so he not end its turn
    if (!selected)
        return false;
    else
    {
        // Sanction selected player, so its can't gather ot tax next turn
        current->sanction(selected);

        // Turns end
        return true;
    }
}

bool Game::coup(Player* current)
{
    // Sets player picker title
    stringstream label;
    label << current->getName() << " You have " << current->getCoins() << " coins\n" <<
             "Choose player to coup";

    // Choose other player to coup, by player picker window
    Player* selected = this->openPlayerPicker(label.str());

    // If user canceled action, so he not end its turn
    if (!selected)
        return false;
    else
    {
        bool isBlocked = false;

        // Runs on all other players that can block coup, aka generals
        // and have enough coins
        for (Player* p : PlayersList::getInstance())
            if (p->getAbility() == Player::BLOCK_COUP && p->getCoins() >= 5)
            {
                // Creates decision title
                stringstream decision;
                decision << "       " << p->getName() << 
                "\ndo you want to pay 5 coins for block " << current->getName() << 
                " from coup" << selected->getName() << '?';

                // Ask other player if want to block from coup, so block action
                // by paying 5 coins, and user lost it turn
                if (this->openDecisionWindow(decision.str()))
                {
                    p->getCoins() -= 5;
                    return true;
                }
            }
        
        // Eliminate selected player from the game
        current->coup(selected);          
        
        // Indicate that turn ends
        return true;
    }
}

void Game::exchange(Player *current)
{
    // Check if this player can exchange, aka Baron
    // and if have enough coins to do it
    if (current->getAbility() == Player::EXCHANGE && current->getCoins() >= 3)
    {
        // Sets decision title
        stringstream label;
        label <<  "          " << current->getName() << "\nDo you want to exchange 3 coins by 6?";

        // Ask if want to exchange, so gain 3 coins
        if (this->openDecisionWindow(label.str()))
            current->getCoins() += 3;
    }
}

void Game::spying(Player *current)
{
    // Check if this player is spy
    if (current->getAbility() == Player::SPYING)
    {
        // Sets decision title
        stringstream label;
        label << "          " << current->getName() << "\nDo you want to spying?";

        // Ask if want to spying
        if (this->openDecisionWindow(label.str()))
        {
            // Choose other player to spy, by player picker window
            Player* selected = this->openPlayerPicker("Choose player to spy");

            // If select player
            if (selected)
            {
                // Sets decision title
                stringstream label;
                label << selected->getName() << " have " << selected->getCoins() << " coins" <<
                "\nDo you want to block him from arrest next turn?";

                // Ask if want to prevent selected player from arrest next turn,
                // so block is ability to arrest
                if (this->openDecisionWindow(label.str()))
                    selected->getIsBlockArrest() = true;
            }
        }
    }
}

void Game::turn() const
{
    // Print to console current turn player name
    cout << PlayersList::getInstance().current()->getName();
}