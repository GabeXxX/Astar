//
// Created by Gabriele Bruni on 2019-07-31.
//

#ifndef ASTAR_BUTTON_H
#define ASTAR_BUTTON_H

#include <SFML/Graphics.hpp>

class Button {
private:

    int x;

    int y;

    std::string text;

    sf::RectangleShape shapeButton;

    sf::Text textButton;

    sf::Font fontButton;

public:
    Button(float width, float height, std::string text);

    void draw(sf::RenderWindow& window);

    bool clicked(sf::Event& event);

    static const int BUTTON_WIDTH = 250;

    static const int BUTTON_HEIGHT = 100;

};


#endif //ASTAR_BUTTON_H
