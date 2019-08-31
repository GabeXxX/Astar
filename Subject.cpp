//
// Created by Gabriele Bruni on 2019-07-30.
//

#include "Subject.h"


void Subject::register_observer(Observer &o) {
    observers.push_back(o);
}

void Subject::notify_observers(GridLocation &locPut, std::string description) {
    for (Observer &o : observers) {
        o.update(locPut, description);
    }
}
