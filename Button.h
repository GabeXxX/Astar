//
// Created by Gabriele Bruni on 2019-07-31.
//

#ifndef ASTAR_BUTTON_H
#define ASTAR_BUTTON_H

#include <SFML/Graphics.hpp>

class Button {
private:
    const int BUTTON_WIDTH = 200;
    const int BUTTON_HEIGHT = 100;
    int x;
    int y;
    sf::RectangleShape shapeButton;
    sf::Text textButton;
    sf::Font fontButton;

public:
    Button(float width, float height, std::string text);

    void draw(sf::RenderWindow& window);

};



#endif //ASTAR_BUTTON_H
