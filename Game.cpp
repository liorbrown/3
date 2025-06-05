// liorbrown@outlook.co.il

#include <sstream>
#include <vector>
#include "Game.hpp"
#include "Player.hpp"
#include <cassert>

Game* Game::instance = nullptr;

Game &Game::getInstance()
{
    if (!instance)
        instance = new Game;
    
    return (*instance);
}

void Game::free()
{
    if (instance)
    {
        delete instance;
        instance = nullptr;
    }
}

void Game::openStartWindow()
{
    Text title{"Welcome to coup!", this->font};

    title.setColor(Color::Black);
    title.setPosition({115.f, 50.f});
    title.setScale({2.f,2.f});

    Button start{{300.f, 270.f},"New Game", this->window};

    while (this->window.isOpen())
    {
        Event event;
        while (this->window.pollEvent(event))
        {
            if (event.type == Event::EventType::Closed)
                this->window.close();
            else if (event.type == Event::EventType::MouseButtonPressed && start.isClicked(event))
                this->openPlayersInitWindow();

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

    Text title{"Insert player 1 name:",this->font};
    title.setPosition({270.f, 80.f});
    title.setFillColor(Color::Black);

    RectangleShape rect{{300.f, 70.f}};
    rect.setPosition({260.f, 180.f});
    rect.setFillColor(Color::White);

    Text input{"",this->font,30};
    input.setPosition({330.f, 195.f});
    input.setColor(Color::Black);

    Text message{"",this->font,30};
    message.setPosition({315.f, 280.f});
    message.setColor(Color::Red);

    Button insert{{300.f, 330.f}, "Add Player", this->window, false};

    Text list{"",this->font,30};
    list.setPosition({330.f, 410.f});
    list.setColor(Color::Black);

    Button start{{300.f, 650.f}, "Start Game", this->window, false}; 

    size_t nPlayer = 1;

    PlayersList::getInstance().clear();

    while (this->window.isOpen())
    {
        Event event;
        while (this->window.pollEvent(event))
        {
            if (event.type == Event::EventType::Closed)
                this->window.close();
            else if (event.type == sf::Event::TextEntered && !title.getString().isEmpty())
            {
                if (event.text.unicode != '\b')
                    playerInput +=event.text.unicode;
                else if(!playerInput.empty())
                    playerInput.erase(playerInput.size() - 1, 1);
                
                input.setString(playerInput);
                insert.getIsEnable() = !playerInput.empty();
            }
            else if (event.type == Event::EventType::MouseButtonPressed)
            {
                if (insert.isClicked(event))
                {
                    if (!PlayersList::getInstance().newPlayer(playerInput))
                        message.setString("Name already exist");
                    else
                    {
                        message.setString("");
                        playerInput.clear();
                        insert.getIsEnable() = false;
                        input.setString("");
                        list.setString(PlayersList::getInstance().getListString());

                        if (nPlayer == 6)
                            title.setString("");    
                        else
                        {
                            title.setString("Insert player " + to_string(++nPlayer) + " name");

                            if (nPlayer == 3)
                                start.getIsEnable() = true;
                        }
                    }
                }
                else if (start.isClicked(event))
                {
                    this->openTurnsWindow();
                }
            }

            this->window.clear(Color::Cyan);

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
    Text title{"",this->font};
    title.setPosition({270.f, 40.f});
    title.setFillColor(Color::Black);

    Button gather{{140.f, 160.f}, "Gather", this->window};
    Button tax{{140.f, 260.f}, "Tax", this->window};
    Button bribe{{140.f, 360.f}, "Bribe", this->window};
    Button arrest{{390.f, 160.f}, "Arrest", this->window};
    Button sanction{{390.f, 260.f}, "Sanction", this->window};
    Button coup{{390.f, 360.f}, "Coup", this->window};
    Button skip{{265.f, 460.f}, "Skip", this->window};

    Text list{PlayersList::getInstance().getListString(), this->font};
    list.setPosition({250.f, 565.f});
    list.setFillColor(Color::Black);

    Player* current;

    while ((current = PlayersList::getInstance().getNext()) && this->window.isOpen())
    {
        ++this->turnNum;

        current->increaseCoins();
        this->exchange(current);
        this->spying(current);
        
        if (current->getCoins() >= 10)
        {
            this->coup(current);
            list.setString(PlayersList::getInstance().getListString());
        }
        else
        {
            bool next = false;

            while (!next && this->window.isOpen())
            {
                stringstream titleStr;
                titleStr << "     " << current->getName() << 
                        " turn\nyou have " << 
                        current->getCoins() << " coins";
                title.setString(titleStr.str());

                gather.getIsEnable() = tax.getIsEnable() = !current->getIsSanctioned();
                bribe.getIsEnable() = current->getCoins() >= 4 && !current->getIsBribe();
                arrest.getIsEnable() = !current->getIsBlockArrest();
                sanction.getIsEnable() = current->getCoins() >= 3;
                coup.getIsEnable() = current->getCoins() >= 7;

                Event event;

                while (this->window.pollEvent(event))
                {
                    if (event.type == Event::EventType::Closed)
                        this->window.close();
                    else if (event.type == Event::EventType::MouseButtonPressed)
                    {
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
                            list.setString(PlayersList::getInstance().getListString());
                        }
                        else if (skip.isClicked(event))
                            next = true;
                    }
                }

                this->window.clear(Color::Cyan);

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

            current->getIsSanctioned() = current->getIsBlockArrest() = false;
        }
    }

    this->winnerName = PlayersList::getInstance().current()->getName();
    this->openFinishWindow();
}

void Game::openFinishWindow()
{
    Text title{"And the winner is\n        " + this->winnerName, this->font};

    title.setColor(Color::Black);
    title.setPosition({115.f, 50.f});
    title.setScale({2.f,2.f});

    Button start{{300.f, 270.f},"New Game", this->window};
    Button close{{300.f, 500.f},"Close", this->window};

    while (this->window.isOpen())
    {
        Event event;
        while (this->window.pollEvent(event))
        {
            if (event.type == Event::EventType::Closed)
                this->window.close();
            else if (event.type == Event::EventType::MouseButtonPressed)
            {
                if (start.isClicked(event))
                    this->openPlayersInitWindow();
                if (close.isClicked(event))
                this->window.close();
            }

            this->window.clear(Color::Cyan);
            this->window.draw(title);
            start.draw();
            close.draw();
            
            this->window.display();
        }
    } 
}

bool Game::openDecisionWindow(string label)
{
    RenderWindow window{VideoMode(800, 400), "Coup"};
    window.requestFocus();

    Text title{label, this->font};

    title.setColor(Color::Black);
    title.setPosition({140.f, 50.f});

    Button yes{{120.f,250.f},"Yes", window};
    Button no{{500.f, 250.f},"No", window};

    enum yesNo
    {
        NONE,
        NO,
        YES
    };

    yesNo decision = NONE;

    while (decision == NONE)
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::EventType::MouseButtonPressed)
            {
                if (yes.isClicked(event))
                    decision = YES;
                else if (no.isClicked(event))
                    decision = NO;
            }

            window.clear(Color::Cyan);
            window.draw(title);
            yes.draw();
            no.draw();
            window.display();
        }
    }

    window.close();
    return (decision == YES);
}

Player *Game::openPlayerPicker(string label, actionType action)
{
    RenderWindow window{VideoMode(800, 750), "Coup"};
    window.requestFocus();

    Text title{label, this->font};

    title.setColor(Color::Black);
    title.setPosition({140.f, 50.f});

    vector<Button> buttons;
    float y = 100.f;

    for (Player* p: PlayersList::getInstance())
    {
        bool enable = !((action == ARREST && 
                        p->getArrestedTurn() &&
                        Game::getInstance().getTurnNum() - p->getArrestedTurn() == 1) ||
                        action == SANCTION && p->getIsSanctioned());

        buttons.emplace_back(Button{{330.f, y += 100}, p->getName(), window, enable});
    }

    Button cancel {{330.f, y += 100}, "Cancel", window};

    Player* selected = nullptr;
    bool isCanceled = false;

    while (!(isCanceled || selected))
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::EventType::MouseButtonPressed &&
                !(isCanceled = cancel.isClicked(event)))
            {
                for (const Button& b : buttons)
                    if (b.isClicked(event))
                    {
                        selected = PlayersList::getInstance().getPlayer(b.getLabel());
                        break;
                    }            
            }

            window.clear(Color::Cyan);
            window.draw(title);

            for (Button& b : buttons)
                b.draw();

            cancel.draw();
            window.display();
            window.requestFocus();
        }
    }
    
    window.close();
    return selected;
}

void Game::arrestedFailed()
{
    RenderWindow window{VideoMode(600, 300), "Coup"};
    window.requestFocus();

    Text title{"Arrested failed, player didn't had coins", this->font};

    title.setColor(Color::Black);
    title.setPosition({60.f, 50.f});

    Button close{{200.f, 200.f},"Close", window};

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::EventType::MouseButtonPressed && close.isClicked(event))
                window.close();

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
    current->gather();
    return true;
}

bool Game::tax(Player* current)
{
    bool isBlocked = false;

    for (Player* p : PlayersList::getInstance())
        if (p->getAbility() == Player::BLOCK_TAX)
        {
            stringstream decision;
            decision << "       " << p->getName() << 
            "\ndo you want to block " << current->getName() << " from taxing?";
            if (isBlocked = this->openDecisionWindow(decision.str())) break;
        }

    if (!isBlocked)
        current->tax();
    
    return true;
}

bool Game::bribe(Player* current)
{
     bool isBlocked = false;

    for (Player* p : PlayersList::getInstance())
        if (p->getAbility() == Player::BLOCK_BRIBE)
        {
            stringstream decision;
            decision << "       " << p->getName() << 
            "\ndo you want to block " << current->getName() << " from bribe?";
            if (isBlocked = this->openDecisionWindow(decision.str())) break;
        }

    if (isBlocked)
        return true;
    else
    {
        current->bribe();
        return false;
    }
}

bool Game::arrest(Player* current)
{
    Player* selected = this->openPlayerPicker("Choose player to arrest", ARREST);

    if (!selected)
        return false;
    else
    {
        if (!selected->arrested())
            this->arrestedFailed();

        return true;
    }
}

bool Game::sanction(Player* current)
{
    Player* selected = this->openPlayerPicker("Choose player to sanction", SANCTION);

    if (!selected)
        return false;
    else
    {
        current->sanction(selected);
        return true;
    }
}

bool Game::coup(Player* current)
{
    stringstream label;

    label << current->getName() << " You have " << current->getCoins() << " coins\n" <<
             "Choose player to coup";

    Player* selected = this->openPlayerPicker(label.str());

    if (!selected)
        return false;
    else
    {
        bool isBlocked = false;

        for (Player* p : PlayersList::getInstance())
            if (p->getAbility() == Player::BLOCK_COUP && p->getCoins() >= 5)
            {
                stringstream decision;
                decision << "       " << p->getName() << 
                "\ndo you want to pay 5 coins for block " << current->getName() << 
                " from coup" << selected->getName() << '?';

                if (isBlocked = this->openDecisionWindow(decision.str()))
                {
                    p->getCoins() -= 5;
                    break;
                }
            }
        
        if (!isBlocked)
            current->coup(selected);          
        
        return true;
    }
}

void Game::exchange(Player *current)
{
    if (current->getAbility() == Player::EXCHANGE && current->getCoins() >= 3)
    {
        stringstream label;
        label <<  "          " << current->getName() << "\nDo you want to exchange 3 coins by 6?";

        if (this->openDecisionWindow(label.str()))
            current->getCoins() += 3;
    }
}

void Game::spying(Player *current)
{
    if (current->getAbility() == Player::SPYING)
    {
        stringstream label;
        label << "          " << current->getName() << "\nDo you want to spying?";

        if (this->openDecisionWindow(label.str()))
        {
            Player* selected = this->openPlayerPicker("Choose player to spy");

            if (selected)
            {
                stringstream label;
                label << selected->getName() << " have " << selected->getCoins() << " coins" <<
                "\nDo you want to block him from arrest next turn?";

                if (this->openDecisionWindow(label.str()))
                    selected->getIsBlockArrest() = true;
            }
        }
    }
}

void Game::turn() const
{
    cout << PlayersList::getInstance().current()->getName();
}