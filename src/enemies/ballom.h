#ifndef BALLOM_H
#define BALLOM_H

#include "core/map.h"
#include "enemies/enemy.h"

typedef struct {
  Enemy enemy;
} Ballom;

Ballom *ballom_create(GridPosition spawn_grid);

void ballom_update(Entity *self);
void ballom_draw(Entity *self);

#endif
