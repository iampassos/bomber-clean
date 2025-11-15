#ifndef POWER_UP_H
#define POWER_UP_H

#include "core/animation.h"
#include "core/map.h"
#include "entity.h"

// tipos de power up do jogo
typedef enum {
  POWER_UP_LIFE,
  POWER_UP_SPEED,
  POWER_UP_BOMB,
  POWER_UP_RADIUS,
  POWER_UP_MAXIMUM_RADIUS,
  POWER_UP_INVENCIBLE,
} PowerUpType;

typedef struct {
  Entity entity;
  bool active;
  PowerUpType power_up_type;
  Animation tick_animation;
  Animation explosion_animation;
} PowerUp;

PowerUp *power_up_create(Vector2 position, PowerUpType type);

void power_up_update(Entity *self);
void power_up_draw(Entity *self);
void power_up_debug(Entity *self);

PowerUp *power_up_at_grid(GridPosition grid); //aparti de um grid position retorna um power up caso exista.

#endif
