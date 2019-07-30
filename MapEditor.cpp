//
// Created by Gabriele Bruni on 2019-07-30.
//

#include "MapEditor.h"

MapEditor::MapEditor(Grid &grid) : grid(grid),
                                    MAP_HEIGHT(grid.height),
                                     MAP_WIDTH(grid.width),
                                      TILE_WIDTH(( (WINDOW_WIDTH-CONTROL_PANE_WIDTH) /MAP_WIDTH)),
                                       TILE_HEIGHT((WINDOW_HEIGHT/MAP_HEIGHT)),
                                        cellSize(TILE_WIDTH, TILE_HEIGHT),
                                         window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MapEditor"){

    //instantiate 2d object array for the map
    map = new sf::RectangleShape*[MAP_WIDTH];
    for (int i = 0; i < MAP_WIDTH; ++i)
        map[i] = new sf::RectangleShape[MAP_HEIGHT];
    //create the map
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {

            map[i][j] = tile;
            map[i][j].setSize(cellSize);
            map[i][j].setPosition(sf::Vector2f(i*TILE_WIDTH + TILE_THICKNESS, j*TILE_HEIGHT+ TILE_THICKNESS));
            map[i][j].setFillColor(sf::Color::White);
            map[i][j].setOutlineColor(sf::Color::Blue);
            map[i][j].setOutlineThickness(5.0f);

        }

    }

}




void MapEditor::addWalls() {


}

void MapEditor::addForests() {

}

void MapEditor::run() {
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }

}

void MapEditor::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        // "close requested" event: we close the renderWindow
        if (event.type == sf::Event::Closed)
            window.close();
    }

}

void MapEditor::update() {

}

void MapEditor::render() {
    window.clear(sf::Color::Black);

    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {

            window.draw(map[i][j]);

        }
    }

    window.display();
}
