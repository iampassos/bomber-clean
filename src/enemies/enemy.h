#ifndef ENEMY_H
#define ENEMY_H

#include "entities/entity.h"

typedef enum { ENEMY_BALLOM } EnemyType;

typedef struct {
  Entity base;
  EnemyType type;
} Enemy;

#endif
