#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>

typedef struct Entity {
  Vector2 position;
  float width;
  float height;

  void (*update)(struct Entity *self);
  void (*draw)(struct Entity *self);
} Entity;

#endif
