#ifndef ENEMY_H
#define ENEMY_H

#include "core/animation.h"
#include "core/map.h"
#include "entities/entity.h"

typedef enum { ENEMY_BALLOM } EnemyType;

typedef struct {
  Entity entity;
  EnemyType type;
  float speed;
  bool alive;
  Animation walk_animation;
  Animation death_animation;
  Animation spawn_animation;
} Enemy;

Enemy *enemy_at_grid(GridPosition grid);

#endif
