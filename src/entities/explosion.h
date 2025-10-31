#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "core/map.h"
#include "entity.h"
#include <raylib.h>

// cima direita baixo esquerda

typedef struct {
  Entity entity;
  int radius;
  GridPosition affected[4 * GRID_WIDTH];
  int affected_length;
  GridPosition destroyed[4 * GRID_WIDTH];
  int destroyed_length;
} Explosion;

Explosion *explosion_create(int radius, Vector2 position);

void explosion(Entity *self);

#endif
