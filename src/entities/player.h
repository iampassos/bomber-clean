#ifndef PLAYER_H
#define PLAYER_H

#include "core/animation.h"
#include "core/map.h"
#include "entity.h"
#include "input/input_manager.h"

#define PLAYER_HEIGHT_TOLERANCE 28.5f

typedef enum { STATE_IDLE, STATE_RUNNING, STATE_DEAD } PlayerState;

typedef struct {
  Entity entity;
  int id;
  GridPosition spawn_grid;
  bool alive;
  bool bomb_passthrough;
  bool invencible;
  float invencibility_start;
  int lives;
  float death_life_time;
  PlayerState state;
  int bomb_capacity;
  int bomb_radius;
  float speed;
  PlayerInput input;
  Animation walk_animation;
  Animation death_animation;
  Animation invencible_animation;
} Player;

Player *player_create(int id, GridPosition spawn_grid);

void player_update(Entity *self);
void player_draw(Entity *self);
void player_debug(Entity *self);

int player_get_all_bombs(Player *player, Entity **out);
Player *player_at_grid(GridPosition grid);

#endif
