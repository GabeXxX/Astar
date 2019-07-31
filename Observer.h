//
// Created by Gabriele Bruni on 2019-07-30.
//

#ifndef ASTAR_OBSERVER_H
#define ASTAR_OBSERVER_H

#include "GridLocation.h"


class Observer
{
public:
    virtual void notify(GridLocation& locPut, std::string description) = 0;
};



#endif //ASTAR_OBSERVER_H
