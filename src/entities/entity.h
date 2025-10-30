#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>

typedef enum { ENTITY_PLAYER, ENTITY_BOMB } EntityType;

typedef enum { LAYER_PLAYERS, LAYER_BOMBS } EntityLayer;

typedef struct Entity {
  EntityType type;
  EntityLayer layer;
  Vector2 position;
  float width;
  float height;

  void (*update)(struct Entity *self);
  void (*draw)(struct Entity *self);
  void (*debug)(struct Entity *self);
} Entity;

#endif
