//
// Created by Gabriele Bruni on 2019-07-30.
//

#ifndef ASTAR_MAPVISUALIZER_H
#define ASTAR_MAPVISUALIZER_H


#include <SFML/Graphics.hpp>
#include "Grid.h"


class MapEditor {
private:
    Grid grid;

    const int  WINDOW_WIDTH = 1800;

    const int WINDOW_HEIGHT = 1000;

    const int TILE_THICKNESS = 5;

    const int CONTROL_PANE_WIDTH = 400;

    const int MAP_HEIGHT;

    const int MAP_WIDTH;

    const int TILE_WIDTH;

    const int TILE_HEIGHT;

    sf::Vector2f cellSize;

    sf::RenderWindow window;

    sf::RectangleShape **map;  //2d array contenente le tile della mappa

    sf::RectangleShape tile = sf::RectangleShape(sf::Vector2f(TILE_WIDTH, TILE_HEIGHT));

    GridLocation start;

    GridLocation goal;


public:

    /*Game();
      void run();
    */
    MapEditor(Grid& grid);

    void run();

    void processEvents();

    void update();

    void render();

    void addWalls();

    void addForests();

    void setStart();

    void setGoal();
};


#endif //ASTAR_MAPVISUALIZER_H
