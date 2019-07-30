


//
// Created by Gabriele Bruni on 2019-07-29.
//

#include <iostream>

#include "Grid.h"
#include "Search.h"
#include "MapEditor.h"

#define MAP_WIDTH 20
#define MAP_HEIGHT 14


int main(){

    /*GridLocation a(1,2);
    GridLocation b(3,1);
    GridLocation c(1,2);
    std::cout<< a <<std::endl;*/


    int x = MAP_WIDTH;
    int y = MAP_HEIGHT;

    Grid map(x,y);

    /*map.setWalls(a);
    map.setWalls(b);
    map.setWalls(GridLocation(1,3));
    std::cout<<map.passable(a)<<std::endl;
    std::cout<<map.passable(GridLocation(3,8))<<std::endl;
    std::cout << '\n';





    GridLocation start(1, 4);
    GridLocation goal(8, 5);
    std::unordered_map<GridLocation, GridLocation> came_from;
    std::unordered_map<GridLocation, double> cost_so_far;
    Search<GridLocation, Grid>::aStar(map, start, goal, came_from, cost_so_far);


    draw_grid(map, 2, nullptr, &came_from);
    std::cout << '\n';
    draw_grid(map, 3, &cost_so_far, nullptr);
    std::cout << '\n';*/

    MapEditor editor(map);
    editor.run();

    draw_grid(map, 2, nullptr, nullptr);
    std::cout << '\n';


}
