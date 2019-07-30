


//
// Created by Gabriele Bruni on 2019-07-29.
//

#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <vector>
#include <utility>
#include <queue>
#include <tuple>
#include <algorithm>
#include <cstdlib>

#include "Grid.h"
#include "Search.h"
#include "MapEditor.h"

#define MAP_WIDTH 20
#define MAP_HEIGHT 14


template<class Graph>

inline void draw_grid(const Graph& graph, int field_width,
                      std::unordered_map<GridLocation, double>* distances=nullptr,
                      std::unordered_map<GridLocation, GridLocation>* point_to=nullptr,
                      std::vector<GridLocation>* path=nullptr) {
    for (int y = 0; y != graph.height; ++y) {
        for (int x = 0; x != graph.width; ++x) {
            GridLocation id (x, y);
            std::cout << std::left << std::setw(field_width);
            if (graph.walls.find(id) != graph.walls.end()) {
                std::cout << std::string(field_width, '#');
            } else if (point_to != nullptr && point_to->count(id)) {
                GridLocation next = (*point_to)[id];
                if (next.x == x + 1) { std::cout << "> "; }
                else if (next.x == x - 1) { std::cout << "< "; }
                else if (next.y == y + 1) { std::cout << "v "; }
                else if (next.y == y - 1) { std::cout << "^ "; }
                else { std::cout << "* "; }
            } else if (distances != nullptr && distances->count(id)) {
                std::cout << (*distances)[id];
            } else if (path != nullptr && find(path->begin(), path->end(), id) != path->end()) {
                std::cout << '@';
            } else {
                std::cout << '.';
            }
        }
        std::cout << '\n';
    }
}

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
