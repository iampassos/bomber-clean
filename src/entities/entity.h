#ifndef ENTITY_H
#define ENTITY_H

#include "core/map.h"
#include <raylib.h>

typedef enum {
  ENTITY_PLAYER,
  ENTITY_BOMB,
  ENTITY_EXPLOSION_TILE,
  ENTITY_POWER_UP,
  ENTITY_ENEMY,
} EntityType;

typedef enum {
  LAYER_PLAYERS,
  LAYER_ENEMIES,
  LAYER_BOMBS,
  LAYER_POWER_UPS
} EntityLayer;

typedef enum {
  DIR_UP,
  DIR_DOWN,
  DIR_LEFT,
  DIR_RIGHT,
} EntityDirection;

typedef struct Entity {
  EntityType type;
  EntityLayer layer;
  EntityDirection direction;
  Vector2 position;
  float width;
  float height;
  float spawn_time;
  float height_tolerance;

  void (*update)(struct Entity *self);
  void (*draw)(struct Entity *self);
  void (*debug)(struct Entity *self);
} Entity;

Vector2 entity_grid_to_world(Entity *entity, GridPosition grid);
GridPosition entity_world_to_grid(Entity *entity);

#endif
