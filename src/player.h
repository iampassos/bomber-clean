#ifndef PLAYER_H
#define PLAYER_H

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
  int animation_step;
  float last_animation_step;
} Player;

extern const char *PLAYER_IMAGES_PATH[4][3];
extern Texture2D PLAYER_TEXTURES[4][3];

void player_init();
void player_new(int id, Vector2 position, float width, float height);
int player_can_move(Vector2 projected, float width, float height);
void player_update(Player *player, float x, float y);
void player_update_all();
void player_debug_draw();

#endif
