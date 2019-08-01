//
// Created by Gabriele Bruni on 2019-07-30.
//

#include "MapEditor.h"
#include "Search.h"
#include "Button.h"

MapEditor::MapEditor() :             grid(MAP_WIDTH,MAP_HEIGHT),
                                      TILE_WIDTH(( (WINDOW_WIDTH-CONTROL_PANE_WIDTH) /MAP_WIDTH)),
                                       TILE_HEIGHT((WINDOW_HEIGHT/MAP_HEIGHT)),
                                        cellSize(TILE_WIDTH, TILE_HEIGHT),
                                         window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MapEditor"),
                                          start(0,0),
                                           goal(MAP_WIDTH-1,MAP_HEIGHT-1){

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

    Search s(*(this));

    s.aStar(grid, start, goal, came_from, cost_so_far);

    s.reconstruct_path(start, goal, came_from);
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

        if (menu[0].clicked(event)) {

            startSearch();
         }
        if (menu[1].clicked(event)) {

             resetGrid();
         }
        if (menu[2].clicked(event)) {
             instructions();
         }
        if (menu[3].clicked(event)) {
             settings();
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
    window.clear(sf::Color(36,36,37));


    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {

            window.draw(map[i][j]);

        }
    }

    menu[0].draw(window);
    menu[1].draw(window);
    menu[2].draw(window);
    menu[3].draw(window);



    window.display();
}

void MapEditor::notify(GridLocation& locPut, std::string description) {

    sf::sleep(sf::milliseconds(DELAY));

    int i = locPut.x;
    int j = locPut.y;

    if(description == "FRONTIER"){
        map[i][j].setFillColor(sf::Color::Cyan);
    }else if(description == "NEXT"){
        map[i][j].setFillColor(sf::Color::Yellow);
    } else if (description == "RECONSTRUCT"){
        map[i][j].setFillColor(sf::Color::Blue);
    }


    render();

}

MapEditor::~MapEditor() {
    // free dynamically allocated memory
    for( int i = 0 ; i < MAP_WIDTH ; i++ )
    {
        delete[] map[i]; // delete array within matrix
    }
// delete actual matrix
    delete[] map;

}

void MapEditor::resetGrid() {

    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            map[i][j].setFillColor(sf::Color::White);
        }
    }

    start.x = 0;
    start.y = 0;
    map[start.x][start.y].setFillColor(sf::Color::Magenta);

    goal.x = MAP_WIDTH-1;
    goal.y = MAP_HEIGHT-1;
    map[start.x][start.y].setFillColor(sf::Color::Red);

    grid.forests.clear();

    grid.walls.clear();

    came_from.clear();

    cost_so_far.clear();


}

void MapEditor::instructions() {
    sf::RenderWindow instruction(sf::VideoMode(1500, 600), "Instructions");

    // run the program as long as the window is open
    while (instruction.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (instruction.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                instruction.close();
        }


        instruction.clear(sf::Color(36,36,37));

        // draw everything here...
        sf::Font fontInstruction;

        if (!fontInstruction.loadFromFile("../Font/menlo.ttc"))
        {
            // handle error
        }

        sf::Text startText;
        sf::Text goalText;
        sf::Text wallText;
        sf::Text forestText;
        sf::Text runText;
        sf::Text resetText;

        startText.setString("Hold S + Mouse SX on the map to set the start position");
        goalText.setString("Hold G + Mouse SX on the map to set the goal position");
        wallText.setString("Hold W + Mouse SX on the map to create new walls");
        forestText.setString("Hold F + Mouse SX on the map to create new forest");
        runText.setString("Click Run button to start the A* search alghorithm on the current map configuration");
        resetText.setString("Click Reset button to come back to default map configuration. \nReset map every time you want to re-execute A*");

        startText.setFont(fontInstruction);
        goalText.setFont(fontInstruction);
        wallText.setFont(fontInstruction);
        forestText.setFont(fontInstruction);
        runText.setFont(fontInstruction);
        resetText.setFont(fontInstruction);

        startText.setPosition(0,0);
        goalText.setPosition(0,100);
        wallText.setPosition(0,200);
        forestText.setPosition(0,300);
        runText.setPosition(0,400);
        resetText.setPosition(0,500);

        instruction.draw(startText);
        instruction.draw(goalText);
        instruction.draw(wallText);
        instruction.draw(forestText);
        instruction.draw(runText);
        instruction.draw(resetText);

        // end the current frame
        instruction.display();
    }
}

void MapEditor::settings() {

    sf::RenderWindow setting(sf::VideoMode(800, 600), "Settings");

    // run the program as long as the window is open
    while (setting.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (setting.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                setting.close();
        }


        setting.clear(sf::Color(36, 36, 37));

        // draw everything here...
        sf::Font fontSetting;

        if (!fontSetting.loadFromFile("../Font/menlo.ttc")) {
            // handle error
        }

        sf::Text widthText;
        sf::Text heightText;
        sf::Text velocityText;

        widthText.setFont(fontSetting);
        heightText.setFont(fontSetting);
        velocityText.setFont(fontSetting);

        widthText.setString("Grid width: ");
        heightText.setString("Grid height: ");
        velocityText.setString("Velocity(millisecond): ");

        widthText.setPosition(0,50);
        heightText.setPosition(0,250);
        velocityText.setPosition(0,450);


        setting.draw(widthText);
        setting.draw(heightText);
        setting.draw(velocityText);

        Button widthButton(500, widthText.getPosition().y - (widthText.getGlobalBounds().height/2), std::to_string(MAP_WIDTH));
        Button heightButton(500, heightText.getPosition().y - (heightText.getGlobalBounds().height/2), std::to_string(MAP_HEIGHT));
        Button velocityButton(500, velocityText.getPosition().y - (velocityText.getGlobalBounds().height/2), std::to_string(DELAY));

        widthButton.draw(setting);
        heightButton.draw(setting);
        velocityButton.draw(setting);
        // end the current frame
        setting.display();

    }

}
