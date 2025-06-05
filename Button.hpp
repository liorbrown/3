// liorbrown@outlook.co.il

#pragma once

#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Button
{
    private:
        RenderWindow* window;
        RectangleShape rect;
        Text label;
        bool isEnabled;
    
    public:
        Button(const Vector2f position,string label, RenderWindow& window, bool isEnabled = true);

        bool& getIsEnable(){return this->isEnabled;}
        string getLabel() const {return this->label.getString();}
        bool isClicked(const Event& event) const;
        void draw();
};
