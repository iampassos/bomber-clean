#ifndef ENEMY_H
#define ENEMY_H

#include "core/animation.h"
#include "entities/entity.h"

typedef enum { ENEMY_BALLOM } EnemyType;

typedef struct {
  Entity entity;
  EnemyType type;
  Animation walk_animation;
  Animation death_animation;
} Enemy;

#endif
