#ifndef POWER_UP_H
#define POWER_UP_H

#include "entity.h"

typedef enum {
  POWER_UP_LIFE,
  POWER_UP_SPEED,
  POWER_UP_BRICK,
  POWER_UP_BOMB,
  POWER_UP_INVENCIBILITY
} PowerUpType;

typedef struct {
  Entity entity;
  PowerUpType type;
} PowerUp;

PowerUp *power_up_create(Vector2 position, PowerUpType type);

void power_up_update(Entity *self);
void power_up_draw(Entity *self);

#endif