#include "Button.hpp"
#include "Game.hpp"

Button::Button(const Vector2f position, string label, RenderWindow& window, bool isEnabled):
    window(&window),
    rect({200,60}),
    label(label, Game::getInstance().getFont(), 30),
    isEnabled(isEnabled)
{
    // Sets button and label position and color
    this->label.setColor(Color::Black);
    this->label.setPosition({position.x + 33, position.y + 15});
    this->rect.setPosition(position);  
}

void Button::draw()
{
    // Sets button color acording to if it enabled or not
    this->rect.setFillColor(this->isEnabled ? Color::Green : Color{222,218,221});

    // Draw button on its window
    this->window->draw(this->rect);
    this->window->draw(this->label);
}

bool Button::isClicked(const Event &event) const
{
    // Return true only if button enabled and mouse click into its area
    return (this->isEnabled && 
            event.mouseButton.x >= this->rect.getPosition().x && 
            event.mouseButton.x <= this->rect.getPosition().x + this->rect.getSize().x &&
            event.mouseButton.y >= this->rect.getPosition().y && 
            event.mouseButton.y <= this->rect.getPosition().y + this->rect.getSize().y);
}
