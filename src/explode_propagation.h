#ifndef EXPLODE_PROPRAGRETION_H
#define EXPLODE_PROPRAGRETION_H

#include "bomb.h"
#include "common.h"
#include <map.h>
#include <raylib.h>
#include "state.h"


typedef struct{
    GridPosition grid_destroyer[50];
    GridPosition grid_explode_animetion[50];
    int lenght_grid_destroyer;
    int lenght_grid_explode_animetion;
}Bombpropagation;

#endif
