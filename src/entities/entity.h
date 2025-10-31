#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>

typedef enum { ENTITY_PLAYER, ENTITY_BOMB,ENTITY_EXPLOSION} EntityType;

typedef enum { LAYER_PLAYERS, LAYER_BOMBS } EntityLayer;

typedef enum { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT } EntityDirection;

typedef struct Entity {
  EntityType type;
  EntityLayer layer;
  EntityDirection direction;
  Vector2 position;
  float width;
  float height;

  void (*update)(struct Entity *self);
  void (*draw)(struct Entity *self);
  void (*debug)(struct Entity *self);
} Entity;

#endif
