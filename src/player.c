#include "player.h"
#include "common.h"
#include "map.h"
#include <math.h>
#include <raylib.h>
#include <state.h>

#define SPEED 5.0f

void player_new(int id, Vector2 position, float width, float height) {
  Player *player = &state.players[state.player_count++];
  player->id = id;
  player->width = width;
  player->height = height;

  int col = (position.x - MAP_X_OFFSET) / TILE_SIZE;
  int row = (position.y - MAP_Y_OFFSET) / TILE_SIZE;
  col = fmax(0, fmin(col, GRID_WIDTH - 1));

  for (int r = row; r < GRID_HEIGHT; r++) {
    if (state.map.grid[col][r] == TILE_EMPTY) {
      player->position = (Vector2){MAP_X_OFFSET + col * TILE_SIZE,
                                   MAP_Y_OFFSET + r * TILE_SIZE};
      return;
    }
  }

  player->position = (Vector2){MAP_X_OFFSET + col * TILE_SIZE, MAP_Y_OFFSET};
}

int player_can_move(Vector2 projected, float width, float height) {
  int left = (projected.x - MAP_X_OFFSET) / TILE_SIZE;
  int right = (projected.x + width - MAP_X_OFFSET) / TILE_SIZE;
  int top = (projected.y - MAP_Y_OFFSET) / TILE_SIZE;
  int bottom = (projected.y + height - MAP_Y_OFFSET) / TILE_SIZE;

  left = fmax(0, fmin(left, GRID_WIDTH - 1));
  right = fmax(0, fmin(right, GRID_WIDTH - 1));
  top = fmax(0, fmin(top, GRID_HEIGHT - 1));
  bottom = fmax(0, fmin(bottom, GRID_HEIGHT - 1));

  for (int row = top; row <= bottom; row++) {
    for (int col = left; col <= right; col++) {
      if (state.map.grid[row][col] != TILE_EMPTY)
        return 0;
    }
  }

  return 1;
}

void player_update(Player *player, int left, int up, int down, int right) {
  Vector2 projected = player->position;

  if (left)
    projected.x = fmax(MAP_X_OFFSET, player->position.x - SPEED);

  if (right)
    projected.x = fmin(SCREEN_WIDTH - MAP_X_OFFSET - player->width,
                       player->position.x + SPEED);

  if (up)
    projected.y = fmax(MAP_Y_OFFSET, player->position.y - SPEED);

  if (down)
    projected.y = fmin(SCREEN_HEIGHT - MAP_Y_OFFSET - player->height,
                       player->position.y + SPEED);

  if (player_can_move(projected, player->width, player->height))
    player->position = projected;
}

void player_update_all() {
  for (int i = 0; i < state.player_count; i++) {
    player_update(&state.players[i], IsKeyDown(KEY_A), IsKeyDown(KEY_W),
                  IsKeyDown(KEY_S), IsKeyDown(KEY_D));
  }
}
