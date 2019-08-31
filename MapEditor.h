//
// Created by Gabriele Bruni on 2019-07-30.
//

#ifndef ASTAR_MAPVISUALIZER_H
#define ASTAR_MAPVISUALIZER_H


#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Search.h"
#include "Button.h"


class MapEditor : Observer {
private:

    const int WINDOW_WIDTH = 1800;

    const int WINDOW_HEIGHT = 1200;

    const int TILE_THICKNESS = 5;

    const int CONTROL_PANE_WIDTH = 400;

    int DELAY = 5; //in millisecond

    int MAP_WIDTH = 50;

    int MAP_HEIGHT = 40;

    int TILE_WIDTH;

    int TILE_HEIGHT;

    sf::Vector2f cellSize;

    sf::RenderWindow window;

    Grid *grid;

    sf::RectangleShape **map;  //2d array contenente le tile della mappa

    sf::RectangleShape *tile;

    GridLocation start;

    GridLocation goal;

    std::unordered_map<GridLocation, GridLocation> came_from;

    std::unordered_map<GridLocation, double> cost_so_far;

    Button menu[4] = {Button(WINDOW_WIDTH - (CONTROL_PANE_WIDTH / 2) - Button::BUTTON_WIDTH / 2 + TILE_THICKNESS,
                             (WINDOW_HEIGHT / 2) - (Button::BUTTON_HEIGHT / 2) - 300, "Run"),
                      Button(WINDOW_WIDTH - (CONTROL_PANE_WIDTH / 2) - Button::BUTTON_WIDTH / 2 + TILE_THICKNESS,
                             (WINDOW_HEIGHT / 2) - (Button::BUTTON_HEIGHT / 2) - 100, "Reset"),
                      Button(WINDOW_WIDTH - (CONTROL_PANE_WIDTH / 2) - Button::BUTTON_WIDTH / 2 + TILE_THICKNESS,
                             (WINDOW_HEIGHT / 2) - (Button::BUTTON_HEIGHT / 2) + 100, "Instructions"),
                      Button(WINDOW_WIDTH - (CONTROL_PANE_WIDTH / 2) - Button::BUTTON_WIDTH / 2 + TILE_THICKNESS,
                             (WINDOW_HEIGHT / 2) - (Button::BUTTON_HEIGHT / 2) + 300, "Settings")};


public:

    MapEditor();

    virtual ~MapEditor();

    void run();

    void processEvents();

    void update();

    void render();

    void addWalls();

    void addForests();

    void setStart();

    void setGoal();

    void startSearch();

    void resetGrid();

    void instructions();

    void settings();

    void drawMap();

    void update(GridLocation &locPut, std::string description) override;
};


#endif //ASTAR_MAPVISUALIZER_H
