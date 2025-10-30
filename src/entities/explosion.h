#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "entity.h"
#include "core/map.h"
#include <raylib.h>

//cima direita baixo esquerda

typedef struct{
    Entity entity;
    int radius;
    GridPosition limits[4];  //limites da explosao
    int limits_length
}Explosion;

Explosion *explosion_create(int radius,Vector2 position);

void explosion(Entity *self);

#endif
