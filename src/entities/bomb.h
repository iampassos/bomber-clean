#ifndef BOMB_H
#define BOMB_H

#include "entities/entity.h"

typedef struct {
  Entity entity;
  int player_id;
  float radius;
  float spawn_time;
} Bomb;

Bomb *bomb_create(int player_id, Vector2 position, float radius);

void bomb_update(Entity *self);
void bomb_draw(Entity *self);

#endif
