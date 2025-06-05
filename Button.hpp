// liorbrown@outlook.co.il

#pragma once

#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

/// @brief This class represent basic button in SFML
class Button
{
    private:
        RenderWindow* window;
        RectangleShape rect;
        Text label;
        bool isEnabled;
    
    public:
        Button(const Vector2f position,string label, RenderWindow& window, bool isEnabled = true);

        // Geters and seters
        bool& getIsEnable(){return this->isEnabled;}
        string getLabel() const {return this->label.getString();}

        /// @brief Check if button clicked
        /// @param event The event of nouse click that contains mouse coordinate
        /// @return True - if buttom clicked, false - otherwise
        bool isClicked(const Event& event) const;

        /// @brief Draw the button on its window
        void draw();
};
