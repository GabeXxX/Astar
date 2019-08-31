//
// Created by Gabriele Bruni on 2019-07-31.
//
#include "Search.h"

Search::Search(Observer &o) {
    register_observer(o);

}


Search::Search() {

}

double Search::heuristic(GridLocation a, GridLocation b) {
    return std::abs(a.getX() - b.getX()) + std::abs(a.getY() - b.getY());
}

void Search::aStar(Grid graph, GridLocation start, GridLocation goal,
                   std::unordered_map<GridLocation, GridLocation> &came_from,
                   std::unordered_map<GridLocation, double> &cost_so_far) {

    PriorityQueue<GridLocation, double> frontier;

    frontier.put(start, 0);
    notify_observers(start, "FRONTIER");

    came_from[start] = start;
    cost_so_far[start] = 0;

    while (!frontier.empty()) {


        GridLocation current = frontier.get();

        if (current == goal) {
            break;
        }

        for (GridLocation next : graph.neighbors(current)) {

            notify_observers(next, "NEXT");

            double new_cost = cost_so_far[current] + graph.cost(current, next);
            if (cost_so_far.find(next) == cost_so_far.end()
                || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                double priority = new_cost + heuristic(next, goal);
                frontier.put(next, priority);
                notify_observers(next, "FRONTIER");
                came_from[next] = current;
            }
        }
    }
}

std::vector<GridLocation> Search::reconstruct_path(GridLocation start, GridLocation goal,
                                                   std::unordered_map<GridLocation, GridLocation> came_from) {
    std::vector<GridLocation> path;
    GridLocation current = goal;
    while (current != start) {
        path.push_back(current);
        current = came_from[current];
        notify_observers(current, "RECONSTRUCT");
    }
    path.push_back(start); // optional
    std::reverse(path.begin(), path.end());
    return path;
}


void Search::register_observer(Observer &o) {
    Subject::register_observer(o);
}

void Search::notify_observers(GridLocation &locPut, std::string description) {
    Subject::notify_observers(locPut, description);
}

