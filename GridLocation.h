//
// Created by Gabriele Bruni on 2019-07-30.
//

#ifndef ASTAR_GRIDLOCATION_H
#define ASTAR_GRIDLOCATION_H


#include <tuple>
#include <iostream>



class GridLocation {

public:
    GridLocation(int x, int y);

    GridLocation();

    int x;

    int y;
};

namespace std {
/* implement hash function so we can put GridLocation into an unordered_set */
    template <> struct hash<GridLocation> {
        typedef GridLocation argument_type;
        typedef std::size_t result_type;
        std::size_t operator()(const GridLocation& id) const noexcept {
            return std::hash<int>()(id.x ^ (id.y << 4));
        }
    };
}

bool operator == (GridLocation a, GridLocation b);

bool operator != (GridLocation a, GridLocation b);

bool operator < (GridLocation a, GridLocation b);

std::basic_iostream<char>::basic_ostream& operator<<(std::basic_iostream<char>::basic_ostream& out, const GridLocation& loc);



/*  WHY I USE PUBLIC DATA MEMBER

private data members are generally considered good because they provide encapsulation.

Providing getters and setters for them breaks that encapsulation, but it's still better than public

data members because there's only once access point to that data.

You'll notice this during debugging. If it's private, you know you can only modify

the variable inside the class. If it's public, you'll have to search the whole code-base for where it might be modified.

As much as possible, ban getters/setters and make properties private.

This follows the principle of information hiding - you shouldn't care about what properties a class has.

It should be self-contained. Of course, in practice this isn't feasible, and if it is,

a design that follows this will be more cluttered and harder to maintain than one that doesn't.

This is of course a rule of thumb - for example, I'd just use a struct

(equivalent with a class with public access) for, say, a simple point class:

struct Point2D
{
   double x;
   double y;
};*/


#endif //ASTAR_GRIDLOCATION_H
