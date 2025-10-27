#include "player.h"
#include "common.h"
#include <math.h>
#include <raylib.h>
#include <stdlib.h>

#define SPEED 10.0f
#define MAX_PLAYERS 1

Player *players[MAX_PLAYERS];
int player_count = 0;

Player *player_new(int id, Vector2 position, float width, float height) {
  Player *player = malloc(sizeof(Player));
  player->id = id;
  player->position = position;
  player->width = width;
  player->height = height;
  players[player_count++] = player;
  return player;
}

void player_update(Player *player, int left, int up, int down, int right) {
  if (left)
    player->position.x = fmax(0, player->position.x - SPEED);

  if (right)
    player->position.x =
        fmin(SCREEN_WIDTH - player->width, player->position.x + SPEED);

  if (up)
    player->position.y = fmax(0, player->position.y - SPEED);

  if (down)
    player->position.y =
        fmin(SCREEN_HEIGHT - player->height, player->position.y + SPEED);
}

void player_update_all() {
  for (int i = 0; i < player_count; i++) {
    player_update(players[i], IsKeyDown(KEY_A), IsKeyDown(KEY_W),
                  IsKeyDown(KEY_S), IsKeyDown(KEY_D));
  }
}
