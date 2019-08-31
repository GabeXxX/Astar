//
// Created by Gabriele Bruni on 2019-07-30.
//

#include "GridLocation.h"

GridLocation::GridLocation(int x, int y) : x(x), y(y) {

}

GridLocation::GridLocation() {

}

int GridLocation::getX() const {
    return x;
}

void GridLocation::setX(int x) {
    if (x >= 0) {
        GridLocation::x = x;
    } else {
        std::cout << "Error: value must be positive";
    }

}

int GridLocation::getY() const {
    return y;
}

void GridLocation::setY(int y) {
    if (y >= 0) {
        GridLocation::y = y;
    } else {
        std::cout << "Error: value must be positive";
    }
}

bool operator==(GridLocation a, GridLocation b) {
    return a.getX() == b.getX() && a.getY() == b.getY();
}

bool operator!=(GridLocation a, GridLocation b) {
    return !(a == b);
}

bool operator<(GridLocation a, GridLocation b) {
    int aX = a.getX();
    int aY = a.getY();
    int bX = b.getX();
    int bY = b.getY();

    return std::tie(aX, aY) < std::tie(bX, bY);
}

std::basic_iostream<char>::basic_ostream &
operator<<(std::basic_iostream<char>::basic_ostream &out, const GridLocation &loc) {
    out << '(' << loc.getX() << ',' << loc.getY() << ')';
    return out;
}
