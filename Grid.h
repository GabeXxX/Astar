//
// Created by Gabriele Bruni on 2019-07-30.
//

#ifndef ASTAR_GRID_H
#define ASTAR_GRID_H


#include <unordered_set>
#include <array>
#include <vector>
#include "GridLocation.h"



class Grid {
private:
    static std::array<GridLocation, 4> DIRS;

    /*int width;

    int height;

    std::unordered_set<GridLocation> walls;

    std::unordered_set<GridLocation> forests;*/


public:
    int width;

    int height;

    std::unordered_set<GridLocation> walls;

    std::unordered_set<GridLocation> forests;

    Grid(int width, int height);

    bool inBounds(GridLocation id) const;

    bool passable(GridLocation id) const;

    std::vector<GridLocation> neighbors(GridLocation id) const;

    double cost(GridLocation from_node, GridLocation to_node) const;

    void setWalls(int x1, int y1, int x2, int y2);

    void setForests(int x1, int y1, int x2, int y2);

    int getWidth() const;

    int getHeight() const;

};



#endif //ASTAR_GRID_H
