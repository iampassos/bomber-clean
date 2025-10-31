#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "core/animation.h"
#include "core/map.h"
#include "entity.h"
#include <raylib.h>

typedef struct {
  Entity entity;
  bool center;
  float lifetime;
  float spawn_time;
  Animation explosion_animation;
} ExplosionTile;

ExplosionTile *explosion_tile_create(Vector2 position,
                                     EntityDirection direction, bool center);

void explosion_tile_update(Entity *self);
void explosion_tile_draw(Entity *self);

ExplosionTile *explosion_tile_at_grid(GridPosition grid);

#endif
