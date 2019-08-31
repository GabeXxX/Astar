//
// Created by Gabriele Bruni on 2019-07-30.
//

#ifndef ASTAR_SUBJECT_H
#define ASTAR_SUBJECT_H

#include <functional>
#include <vector>
#include "Observer.h"
#include "GridLocation.h"

class Subject {
public:
    virtual void register_observer(Observer &o);

    virtual void notify_observers(GridLocation &locPut, std::string description);

private:
    std::vector<std::reference_wrapper<Observer>> observers;
};

/*
 * The observer pattern allows generic observer objects to be registered with a
 * subject object and receive notifications when certain events occur.
 * The subject class, defined on lines 17–34, contains a std::vector of references
 * to observers line 33. Observers (also known as listeners), in this case, are
 * objects that implement the observer interface (lines 4–8). The register_observer
 * function (lines 20–23) adds observers to this std::vector, which are later
 * to be notified by the notify_observers function (lines 25–30).
 * We use std::reference_wrapper for the elements of the std::vector (line 33),
 * because the standard containers require the element type to be assignable,
 * which normal reference types are not.
 */

#endif //ASTAR_SUBJECT_H
