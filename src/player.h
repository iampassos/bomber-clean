#ifndef PLAYER_H
#define PLAYER_H

#include "animation.h"
#include "common.h"
#include "map.h"
#include <raylib.h>

typedef enum { UP, DOWN, LEFT, RIGHT } Direction;

typedef enum { IDLE, RUNNING, DEAD } PlayerState;

typedef struct Player {
  int id;
  Vector2 position;
  float width;
  float height;
  Direction direction;
  PlayerState state;
  int bomb_capacity;
  float speed;
  int alive;
  Animation walk_animation;
} Player;

typedef struct Players {
  Player entries[MAX_PLAYERS];
  int count;
} Players;

extern const char *PLAYER_IMAGES_PATH[4][3];
extern Texture2D PLAYER_TEXTURES[4][3];

Vector2 player_get_vector_from_grid_position(Player *player, GridPosition pos);
GridPosition player_get_grid_position(Player *player);
void player_init();
void player_new(int id, Vector2 position, float width, float height);
int player_can_move(Vector2 projected, float width, float height);
void player_update(Player *player, float x, float y);
void player_update_all();
void player_debug_draw(Player *p);

#endif
