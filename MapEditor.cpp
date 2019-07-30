//
// Created by Gabriele Bruni on 2019-07-30.
//

#include "MapEditor.h"
#include "Search.h"

MapEditor::MapEditor(Grid &grid) : grid(grid),
                                    MAP_HEIGHT(grid.height),
                                     MAP_WIDTH(grid.width),
                                      TILE_WIDTH(( (WINDOW_WIDTH-CONTROL_PANE_WIDTH) /MAP_WIDTH)),
                                       TILE_HEIGHT((WINDOW_HEIGHT/MAP_HEIGHT)),
                                        cellSize(TILE_WIDTH, TILE_HEIGHT),
                                         window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MapEditor"),
                                          start(0,0),
                                           goal(19,13){

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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        // get the local mouse position (relative to a window)
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        //std::cout<<"Position: "<<"("<<mousePosition.x<<","<<mousePosition.y<<")"<<std::endl;

        //transform in map coordinates
        int i = (mousePosition.x-TILE_THICKNESS)/TILE_WIDTH;
        int j = (mousePosition.y-TILE_THICKNESS)/TILE_HEIGHT;
        //std::cout<<"Position: "<<"("<<i<<","<<j<<")"<<std::endl;

        map[i][j].setFillColor(sf::Color::Black);
        grid.setWalls(GridLocation(i,j));


    }


}

void MapEditor::addForests() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        // get the local mouse position (relative to a window)
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        //std::cout << "Position: " << "(" << mousePosition.x << "," << mousePosition.y << ")" << std::endl;

        //transform in map coordinates
        int i = (mousePosition.x - TILE_THICKNESS) / TILE_WIDTH;
        int j = (mousePosition.y - TILE_THICKNESS) / TILE_HEIGHT;
        //std::cout << "Position: " << "(" << i << "," << j << ")" << std::endl;

        map[i][j].setFillColor(sf::Color::Green);
        grid.setForests(GridLocation(i, j));
    }

}

void MapEditor::setStart() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        // get the local mouse position (relative to a window)
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        //std::cout << "Position: " << "(" << mousePosition.x << "," << mousePosition.y << ")" << std::endl;

        //transform in map coordinates
        int i = (mousePosition.x - TILE_THICKNESS) / TILE_WIDTH;
        int j = (mousePosition.y - TILE_THICKNESS) / TILE_HEIGHT;
        //std::cout << "Position: " << "(" << i << "," << j << ")" << std::endl;

        map[start.x][start.y].setFillColor(sf::Color::White); //reset color

        start.x = i;  //assign new start coordinates
        start.y = j;
    }

    int i = start.x;
    int j = start.y;
    map[i][j].setFillColor(sf::Color::Magenta); //update color on grid for the new start point

}

void MapEditor::setGoal() {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        // get the local mouse position (relative to a window)
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        //std::cout << "Position: " << "(" << mousePosition.x << "," << mousePosition.y << ")" << std::endl;

        //transform in map coordinates
        int i = (mousePosition.x - TILE_THICKNESS) / TILE_WIDTH;
        int j = (mousePosition.y - TILE_THICKNESS) / TILE_HEIGHT;
        //std::cout << "Position: " << "(" << i << "," << j << ")" << std::endl;

        map[goal.x][goal.y].setFillColor(sf::Color::White); //reset color

        goal.x = i;  //assign new goal coordinates
        goal.y = j;
    }


    int i = goal.x;
    int j = goal.y;
    map[i][j].setFillColor(sf::Color::Red); //update color on grid for the new goal point


}

void MapEditor::startSearch() {
    std::cout<<"enter released"<<std::endl;
    std::unordered_map<GridLocation, GridLocation> came_from;
    std::unordered_map<GridLocation, double> cost_so_far;
    Search<GridLocation, Grid>::aStar(grid, start, goal, came_from, cost_so_far);

    draw_grid(grid, 2, nullptr, nullptr);
    std::cout << '\n';
    draw_grid(grid, 2, nullptr, &came_from);
    std::cout << '\n';
    draw_grid(grid, 3, &cost_so_far, nullptr);
    std::cout << '\n';

    std::vector<GridLocation> path = reconstruct_path(start, goal, came_from);
    draw_grid(grid, 3, nullptr, nullptr, &path);
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

        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Enter) {
                startSearch();
            }
        }

    }
}

void MapEditor::update() {
    addWalls();
    addForests();
    setStart();
    setGoal();

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


