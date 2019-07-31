//
// Created by Gabriele Bruni on 2019-07-30.
//

#ifndef ASTAR_SEARCH_H
#define ASTAR_SEARCH_H

#include <unordered_map>
#include <iomanip>
#include <queue>

#include "GridLocation.h"
#include "Subject.h"


template<typename T, typename priority_t>
struct PriorityQueue {
    typedef std::pair<priority_t, T> PQElement;
    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> elements;

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


class Search : Subject{

public:
    Search(Observer& o){
        register_observer(o);

    }

    inline double heuristic(GridLocation a, GridLocation b) {
        return std::abs(a.x - b.x) + std::abs(a.y - b.y);
    }

    void aStar(Grid graph,GridLocation start,GridLocation goal,
                std::unordered_map<GridLocation, GridLocation>& came_from,
                 std::unordered_map<GridLocation, double>& cost_so_far){

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

    inline std::vector<GridLocation> reconstruct_path(
            GridLocation start, GridLocation goal,
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


    void register_observer(Observer &o) override {
        Subject::register_observer(o);
    }

    void notify_observers(GridLocation& locPut, std::string description) override {
        Subject::notify_observers(locPut, description);
    }


};





#endif //ASTAR_SEARCH_H
