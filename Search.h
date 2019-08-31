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
#include "Grid.h"


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


class Search : Subject {

public:

    Search();

    Search(Observer &o);

    double heuristic(GridLocation a, GridLocation b);

    void aStar(Grid graph, GridLocation start, GridLocation goal,
               std::unordered_map<GridLocation, GridLocation> &came_from,
               std::unordered_map<GridLocation, double> &cost_so_far);

    std::vector<GridLocation> reconstruct_path(
            GridLocation start, GridLocation goal,
            std::unordered_map<GridLocation, GridLocation> came_from);

    void register_observer(Observer &o) override;

    void notify_observers(GridLocation &locPut, std::string description) override;

};


#endif //ASTAR_SEARCH_H
