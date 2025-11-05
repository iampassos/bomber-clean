#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "entities/player.h"
#include "libs/linked_list.h"
#include  "map.h"
#include <math.h>
#include "game/game_manager.h"


typedef struct NodeA{
    GridPosition grid;
    int g,h,f;
    struct NodeA *parent;
}NodeA;







#endif
