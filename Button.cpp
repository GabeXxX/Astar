//
// Created by Gabriele Bruni on 2019-07-31.
//

#include <iostream>
#include "Button.h"

Button::Button(float x, float y, std::string text) : x(x), y(y), text(text){

    if (!fontButton.loadFromFile("../Font/menlo.ttc"))
    {
        // handle error
    }

    shapeButton.setPosition(x, y);
    shapeButton.setSize(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
    shapeButton.setFillColor(sf::Color::White);
    shapeButton.setOutlineThickness(5);
    shapeButton.setOutlineColor(sf::Color::Blue);

    textButton.setPosition(x, y);
    textButton.setFont(fontButton);
    textButton.setString(text);
    textButton.setFillColor(sf::Color::Black);
    const sf::FloatRect bounds(textButton.getLocalBounds());
    const sf::Vector2f box(shapeButton.getSize());
    textButton.setOrigin((bounds.width - box.x) / 2 + bounds.left, (bounds.height - box.y) / 2 + bounds.top);

}

void Button::draw(sf::RenderWindow &window) {
    window.draw(shapeButton);
    window.draw(textButton);
}

bool Button::clicked(sf::Event &event) {

    bool one = false;
    bool two = false;
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if(event.mouseButton.x>x && event.mouseButton.x< x+BUTTON_WIDTH &&
                event.mouseButton.y>y && event.mouseButton.y< y+BUTTON_HEIGHT){
                shapeButton.setFillColor(sf::Color(128,128,128));

            }
        }
    }

    if (event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if(event.mouseButton.x>x && event.mouseButton.x< x+BUTTON_WIDTH &&
               event.mouseButton.y>y && event.mouseButton.y< y+BUTTON_HEIGHT){
                shapeButton.setFillColor(sf::Color::White);

                return true;
            }
        }

    }

    return false;

}
