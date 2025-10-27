#ifndef MAP_H
#define MAP_H

#include <common.h>
#include <raylib.h>

typedef enum {
  TILE_EMPTY,
  TILE_WALL,
  TILE_BRICK,
} TileType;

extern const Color TILE_COLORS[3];

typedef struct Map {
  TileType grid[GRID_HEIGHT][GRID_WIDTH];
} Map;

Map *map_init();

#endif
