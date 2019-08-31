//
// Created by Gabriele Bruni on 2019-08-22.
//

#include "gtest/gtest.h"
#include "../Search.h"

std::vector<GridLocation> setUp() {


}


TEST(Astar, blankMap) {

    Search s;
    Grid grid(5, 5);
    GridLocation start(0, 0);
    GridLocation goal(4, 4);
    std::unordered_map<GridLocation, GridLocation> came_from;
    std::unordered_map<GridLocation, double> cost_so_far;

    s.aStar(grid, start, goal, came_from, cost_so_far);

    std::vector<GridLocation> path = s.reconstruct_path(start, goal, came_from);

    std::vector<GridLocation> rightPath;

    rightPath.push_back(GridLocation(0, 0));
    rightPath.push_back(GridLocation(0, 1));
    rightPath.push_back(GridLocation(0, 2));
    rightPath.push_back(GridLocation(0, 3));
    rightPath.push_back(GridLocation(0, 4));
    rightPath.push_back(GridLocation(1, 4));
    rightPath.push_back(GridLocation(2, 4));
    rightPath.push_back(GridLocation(3, 4));
    rightPath.push_back(GridLocation(4, 4));

    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(rightPath[i], path[i]);
    }

}


TEST(Astar, difficultMap) {

    Search s;
    Grid grid(5, 5);

    grid.setForests(GridLocation(0, 1));
    grid.setForests(GridLocation(0, 2));
    grid.setForests(GridLocation(0, 3));
    grid.setForests(GridLocation(1, 1));
    grid.setForests(GridLocation(1, 2));
    grid.setForests(GridLocation(2, 1));
    grid.setForests(GridLocation(4, 1));
    grid.setForests(GridLocation(4, 2));
    grid.setForests(GridLocation(4, 3));

    grid.setWalls(GridLocation(0, 4));
    grid.setWalls(GridLocation(1, 3));
    grid.setWalls(GridLocation(2, 2));
    grid.setWalls(GridLocation(3, 1));

    GridLocation start(0, 0);
    GridLocation goal(4, 4);
    std::unordered_map<GridLocation, GridLocation> came_from;
    std::unordered_map<GridLocation, double> cost_so_far;

    s.aStar(grid, start, goal, came_from, cost_so_far);

    std::vector<GridLocation> path = s.reconstruct_path(start, goal, came_from);

    std::vector<GridLocation> rightPath;

    rightPath.push_back(GridLocation(0, 0));
    rightPath.push_back(GridLocation(1, 0));
    rightPath.push_back(GridLocation(2, 0));
    rightPath.push_back(GridLocation(3, 0));
    rightPath.push_back(GridLocation(4, 0));
    rightPath.push_back(GridLocation(4, 1));
    rightPath.push_back(GridLocation(4, 2));
    rightPath.push_back(GridLocation(3, 2));
    rightPath.push_back(GridLocation(3, 3));
    rightPath.push_back(GridLocation(3, 4));
    rightPath.push_back(GridLocation(4, 4));


    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(rightPath[i], path[i]);
    }

}

TEST(Astar, impossibleMap) {

    Search s;
    Grid grid(5, 5);

    grid.setWalls(GridLocation(0, 4));
    grid.setWalls(GridLocation(1, 3));
    grid.setWalls(GridLocation(2, 2));
    grid.setWalls(GridLocation(3, 1));
    grid.setWalls(GridLocation(4, 0));

    GridLocation start(0, 0);
    GridLocation goal(4, 4);
    std::unordered_map<GridLocation, GridLocation> came_from;
    std::unordered_map<GridLocation, double> cost_so_far;

    s.aStar(grid, start, goal, came_from, cost_so_far);

    std::vector<GridLocation> path = s.reconstruct_path(start, goal, came_from);

    std::vector<GridLocation> rightPath;

    rightPath.push_back(GridLocation(0, 0));
    rightPath.push_back(GridLocation(1, 0));
    rightPath.push_back(GridLocation(2, 0));
    rightPath.push_back(GridLocation(3, 0));
    rightPath.push_back(GridLocation(4, 0));
    rightPath.push_back(GridLocation(4, 1));
    rightPath.push_back(GridLocation(4, 2));
    rightPath.push_back(GridLocation(3, 2));
    rightPath.push_back(GridLocation(3, 3));
    rightPath.push_back(GridLocation(3, 4));
    rightPath.push_back(GridLocation(4, 4));

    for (int i = 0; i < 5; i++) {
        EXPECT_NE(rightPath[i], path[i]);

    }

}

