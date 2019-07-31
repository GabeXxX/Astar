//
// Created by Gabriele Bruni on 2019-07-29.
//

#include <iostream>

#include "Grid.h"
#include "MapEditor.h"

#define MAP_WIDTH 50
#define MAP_HEIGHT 40


int main(){

    int x = MAP_WIDTH;
    int y = MAP_HEIGHT;

    Grid map(x,y);

    MapEditor editor(map);
    editor.run();

}
