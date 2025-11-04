#ifndef ENEMY_H
#define ENEMY_H

#include "core/animation.h"
#include "core/map.h"
#include "entities/entity.h"

typedef enum {
  ENEMY_0,
} EnemyType;

typedef struct {
    Entity entity;
    EnemyType enemy_type;
}Enemy;

#endif
