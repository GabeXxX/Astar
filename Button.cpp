//
// Created by Gabriele Bruni on 2019-07-31.
//

#include "Button.h"

Button::Button(float x, float y, std::string text) : x(x), y(y){

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