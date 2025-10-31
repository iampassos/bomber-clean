#ifndef PLAYER_H
#define PLAYER_H

#include "core/animation.h"
#include "core/map.h"
#include "entity.h"
#include "input/input_manager.h"

typedef enum { STATE_IDLE, STATE_RUNNING, STATE_DEAD } PlayerState;

typedef struct {
  Entity entity;
  int id;
  bool alive;
  int lives;
  PlayerState state;
  int bomb_capacity;
  float speed;
  PlayerInput input;
  Animation walk_animation;
  Animation death_animation;
} Player;

Player *player_create(int id, Vector2 position);

void player_update(Entity *self);
void player_draw(Entity *self);
void player_debug(Entity *self);

Vector2 player_grid_to_world(Player *player, GridPosition pos);
GridPosition player_world_to_grid(Player *player);
int player_get_all_bombs(Player *player, Entity **out);

#endif
