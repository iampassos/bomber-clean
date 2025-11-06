#ifndef BOMB_H
#define BOMB_H

#include "core/animation.h"
#include "core/map.h"
#include "entities/entity.h"

typedef struct {
  Entity entity;
  int player_id;
  bool exploded;
  int radius;
  float spawn_time;
  float explosion_time;
  Animation tick_animation;
  Animation spawn_animation;
} Bomb;

Bomb *bomb_create(int player_id, Vector2 position, int radius);

void bomb_update(Entity *self);
void bomb_draw(Entity *self);

Bomb *bomb_at_grid(GridPosition grid);

#endif
