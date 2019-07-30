//
// Created by Gabriele Bruni on 2019-07-30.
//

#ifndef ASTAR_SEARCH_H
#define ASTAR_SEARCH_H

#include <unordered_map>
#include <iomanip>
#include <queue>

#include "GridLocation.h"


template<typename T, typename priority_t>
struct PriorityQueue {
    typedef std::pair<priority_t, T> PQElement;
    std::priority_queue<PQElement, std::vector<PQElement>,
            std::greater<PQElement>> elements;

    inline bool empty() const {
        return elements.empty();
    }

    inline void put(T item, priority_t priority) {
        elements.emplace(priority, item);
    }

    inline T get() {
        T best_item = elements.top().second;
        elements.pop();
        return best_item;
    }
};

inline double heuristic(GridLocation a, GridLocation b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}


template<typename Location, typename Graph>
class Search {

public:
    inline static void aStar(Graph graph,Location start,Location goal,
            std::unordered_map<Location, Location>& came_from,
            std::unordered_map<Location, double>& cost_so_far){
            PriorityQueue<Location, double> frontier;
            frontier.put(start, 0);

            came_from[start] = start;
            cost_so_far[start] = 0;

            while (!frontier.empty()) {
                Location current = frontier.get();

                if (current == goal) {
                    break;
                }

                for (Location next : graph.neighbors(current)) {
                    double new_cost = cost_so_far[current] + graph.cost(current, next);
                    if (cost_so_far.find(next) == cost_so_far.end()
                        || new_cost < cost_so_far[next]) {
                        cost_so_far[next] = new_cost;
                        double priority = new_cost + heuristic(next, goal);
                        frontier.put(next, priority);
                        came_from[next] = current;
                    }
                }
            }
        }

};


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



#endif //ASTAR_SEARCH_H
