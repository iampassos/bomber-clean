#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>

#define GAMEPLAY_WIDTH 256 * 4
#define GAMEPLAY_HEIGHT 224 * 4

#define TILE_SIZE 64.0f
#define GRID_WIDTH 15
#define GRID_HEIGHT 13
#define GRID_SIZE (GRID_WIDTH * GRID_HEIGHT)

#define MAX_PLAYERS 2
#define MAX_PLAYER_LIVES 5
#define MAX_PLAYER_SPEED 5.0f
#define MAX_PLAYER_BOMBS 5

#define PLAYER_INVENCIBILITY_TIME 15.0f

#define PLAYER_DEFAULT_LIVES 3
#define PLAYER_DEFAULT_SPEED 3.0f

#define DEFAULT_BOMB_RADIUS 1
#define DEFAULT_EXPLOSION_LIFETIME 0.6f
#define DEFAULT_BOMBS 1
#define MAX_BOMB_RADIUS 10

#define POWER_UP_PROBABILITY 10
#define POWER_UP_SPEED_INCREASE (MAX_PLAYER_SPEED * 0.05)
#define POWER_UP_MAP_LIMIT 6
#define POWER_UP_TIMEOUT 60.0f

#define PROBABILITY_SPAWN_TILE_BRICK_ON_MAP 25

extern float MAP_X_OFFSET;
extern float MAP_Y_OFFSET;

void common_update_offset();
bool common_should_update_offset();

#endif
