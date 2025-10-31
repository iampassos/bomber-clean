#ifndef POWER_UP_H
#define POWER_UP_H

#include "entity.h"
#include "core/animation.h"

typedef enum {
  POWER_UP_LIFE,
  POWER_UP_SPEED,
  POWER_UP_BOMB,
} PowerUpType;

typedef struct {
  Entity entity;
  PowerUpType power_up_type;
  float spawn_time;
  Animation tick_animation;
} PowerUp;

PowerUp *power_up_create(Vector2 position, PowerUpType type);

void power_up_update(Entity *self);
void power_up_draw(Entity *self);
void power_up_debug(Entity *self);

#endif
