#ifndef COMMON_H
#define COMMON_H

#include <SDL2/SDL_gamecontroller.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define TILE_SIZE 70
#define GRID_WIDTH 15
#define GRID_HEIGHT 13
#define GRID_SIZE (GRID_WIDTH * GRID_HEIGHT)

#define MAP_X_OFFSET (SCREEN_WIDTH / 2 - TILE_SIZE * GRID_WIDTH / 2)
#define MAP_Y_OFFSET (SCREEN_HEIGHT - GRID_HEIGHT * TILE_SIZE)

#define MAX_PLAYERS 1

extern SDL_GameController *controllers[MAX_PLAYERS];
extern int controllers_n;

#endif
