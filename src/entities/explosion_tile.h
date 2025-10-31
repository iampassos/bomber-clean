#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "core/animation.h"
#include "core/map.h"
#include "entity.h"
#include <raylib.h>

// cima direita baixo esquerda

typedef struct {
  Entity entity;
  float lifetime;
  float spawned;
  Animation explosion_animation;
} ExplosionTile;

ExplosionTile *explosion_tile_create(Vector2 position);

void explosion_tile_update(Entity *self);
void explosion_tile_draw(Entity *self);

#endif
