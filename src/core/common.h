#ifndef COMMON_H
#define COMMON_H

#define SCREEN_WIDTH 256 * 4
#define SCREEN_HEIGHT 224 * 4

#define TILE_SIZE 64.0f
#define GRID_WIDTH 15
#define GRID_HEIGHT 13
#define GRID_SIZE (GRID_WIDTH * GRID_HEIGHT)

#define MAP_X_OFFSET (SCREEN_WIDTH / 2.0f - TILE_SIZE * GRID_WIDTH / 2.0f)
#define MAP_Y_OFFSET                                                           \
  (SCREEN_HEIGHT - GRID_HEIGHT * TILE_SIZE + TILE_SIZE / 2.0f)

#define MAX_PLAYERS 2
#define MAX_PLAYER_LIVES 5
#define MAX_PLAYER_SPEED 5.0f
#define MAX_PLAYER_BOMBS 5

#define PLAYER_DEFAULT_SPEED 3.0f

#define POWER_UP_PROBABILITY 100
#define POWER_UP_SPEED_INCREASE (MAX_PLAYER_SPEED * 0.05)

#endif
