#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

typedef enum { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT } Direction;

typedef enum { STATE_IDLE, STATE_RUNNING, STATE_DEAD } PlayerState;

typedef struct {
  Entity entity;
  int id;
  Direction direction;
  PlayerState state;
  int bomb_capacity;
  float speed;
} Player;

Player *player_create(int id, Vector2 position);

void player_update(Entity *self);
void player_draw(Entity *self);

#endif
