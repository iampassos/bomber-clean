#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "libs/linked_list.h"
#include  "map.h"
#include <math.h>



typedef struct NodeA{
    GridPosition grid;
    int g,h,f;
    struct NodeA *parent;
}NodeA;


GridPosition path_finding(TileType grid[GRID_HEIGHT][GRID_WIDTH], GridPosition star, GridPosition goal);




#endif
