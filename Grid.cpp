//
// Created by Gabriele Bruni on 2019-07-30.
//


#include "Grid.h"



Grid::Grid(int width, int height) : width(width), height(height){
}

bool Grid::inBounds(GridLocation id) const {
    return 0 <= id.x && id.x < width
           && 0 <= id.y && id.y < height;
}

bool Grid::passable(GridLocation id) const {
    return walls.find(id) == walls.end();
}

std::vector<GridLocation> Grid::neighbors(GridLocation id) const {
    std::vector<GridLocation> results;

    for (GridLocation dir : DIRS) {
        GridLocation next{id.x + dir.x, id.y + dir.y};
        if (inBounds(next) && passable(next)) {
            results.push_back(next);
        }
    }

    if ((id.x + id.y) % 2 == 0) {
        // aesthetic improvement on square grids
        std::reverse(results.begin(), results.end());
    }

    return results;

}

double Grid::cost(GridLocation from_node, GridLocation to_node) const {
    return forests.find(to_node) != forests.end()? 5 : 1;
}

void Grid::setWalls(int x1, int y1, int x2, int y2) {
    for (int x = x1; x < x2; x++) {
        for (int y = y1; y < y2; y++) {
            walls.insert(GridLocation(x, y));
        }
    }
}

void Grid::setForests(int x1, int y1, int x2, int y2) {
    for (int x = x1; x < x2; x++) {
        for (int y = y1; y < y2; y++) {
            forests.insert(GridLocation(x, y));
        }
    }
}

int Grid::getWidth() const {
    return width;
}

int Grid::getHeight() const {
    return height;
}

std::array<GridLocation, 4> Grid::DIRS =
        {GridLocation{1, 0}, GridLocation{0, -1}, GridLocation{-1, 0}, GridLocation{0, 1}};


