#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

typedef struct Player {
  int id;
  Vector2 position;
  float width;
  float height;
} Player;

extern Player *players[];
extern int player_count;

Player *player_new(int id, Vector2 position, float width, float height);
void player_update(Player *player, int left, int up, int down, int right);
void player_update_all();

#endif
