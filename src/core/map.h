#ifndef MAP_H
#define MAP_H

#include "common.h"
#include <raylib.h>

typedef enum { MAP_BATTLE_STAGE_1, MAP_STAGE_1 } MapType;

typedef enum {
  TILE_EMPTY,
  TILE_WALL,
  TILE_BRICK,
} TileType;

typedef struct GridPosition {
  int col;
  int row;
} GridPosition;

typedef struct Map {
  TileType grid[GRID_HEIGHT][GRID_WIDTH];
  MapType stage;
} Map;

void map_init(Map *map, MapType map_type);

TileType map_get_tile(Map *map, GridPosition position);
void map_set_tile(Map *map, GridPosition position, TileType tile);
bool map_is_walkable(Map *map, GridPosition position);
bool map_is_same_grid(GridPosition grid1, GridPosition grid2);

GridPosition map_world_to_grid(Vector2 position);
Vector2 map_grid_to_world(GridPosition position);
Vector2 map_grid_to_world_center(GridPosition position);
Rectangle map_get_tile_bounds(GridPosition position);

#endif
