#ifndef MAP_H
#define MAP_H

#include "common.h"
#include <raylib.h>

typedef enum {
  MAP_NORMAL_ZONE,
  MAP_BOMB_ZONE,
  MAP_JUMP_ZONE,
  MAP_DUEL_ZONE,
  MAP_LIGHT_ZONE,
  MAP_SPEED_ZONE,
  MAP_BELT_ZONE,
  MAP_WESTERN_ZONE
} MapType;

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
  int enemies[3];
  int enemies_n;
} Map;

Map *map_create(MapType map_type);
Map *map_next(Map *map);

TileType map_get_tile(Map *map, GridPosition position);
void map_set_tile(Map *map, GridPosition position, TileType tile);
bool map_is_walkable(Map *map, GridPosition position);
bool map_is_same_grid(GridPosition grid1, GridPosition grid2);
bool map_is_valid_grid(GridPosition grid);
bool map_is_valid_position(Vector2 position);

GridPosition map_world_to_grid(Vector2 position);
Vector2 map_grid_to_world(GridPosition position);
Vector2 map_grid_to_world_center(GridPosition position);
Rectangle map_get_tile_bounds(GridPosition position);

#endif
