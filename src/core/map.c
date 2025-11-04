#include "map.h"
#include "core/common.h"
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <time.h>

void map_init(Map *map, MapType map_type) {
  srand(time(NULL));

  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      if (i == 0 || j == 0 || i + 1 == GRID_HEIGHT || j + 1 == GRID_WIDTH ||
          (i % 2 == 0 && j % 2 == 0)) {
        map->grid[i][j] = TILE_WALL;
      } else
        map->grid[i][j] =
            (i != 1 || j != 1) &&
                    rand() % 100 < PROBABILITY_SPAWN_TILE_BRICK_ON_MAP
                ? TILE_BRICK
                : TILE_EMPTY;
    }
  }

  // garantir que tenha laterais empyt no spawn do bomber man
  map->grid[1][2] = TILE_EMPTY;
  map->grid[2][1] = TILE_EMPTY;

  map->stage = map_type;
}

TileType map_get_tile(Map *map, GridPosition position) {
  return map->grid[position.row][position.col];
}

void map_set_tile(Map *map, GridPosition position, TileType tile) {
  map->grid[position.row][position.col] = tile;
}

bool map_is_walkable(Map *map, GridPosition position) {
  return map_get_tile(map, position) == TILE_EMPTY;
}

bool map_is_same_grid(GridPosition grid1, GridPosition grid2) {
  return grid1.col == grid2.col && grid1.row == grid2.row;
}

bool map_is_valid_grid(GridPosition grid) {
  return grid.col >= 0 && grid.col < GRID_WIDTH && grid.row >= 0 &&
         grid.row < GRID_HEIGHT;
}

bool map_is_valid_position(Vector2 position) {
  return map_is_valid_grid(map_world_to_grid(position));
}

GridPosition map_world_to_grid(Vector2 position) {
  return (GridPosition){.col = (position.x - MAP_X_OFFSET) / TILE_SIZE,
                        .row = (position.y - MAP_Y_OFFSET) / TILE_SIZE};
}

Vector2 map_grid_to_world(GridPosition position) {
  return (Vector2){.x = MAP_X_OFFSET + position.col * TILE_SIZE,
                   .y = MAP_Y_OFFSET + position.row * TILE_SIZE};
}

Vector2 map_grid_to_world_center(GridPosition position) {
  return (Vector2){.x = MAP_X_OFFSET + position.col * TILE_SIZE + TILE_SIZE / 2,
                   .y =
                       MAP_Y_OFFSET + position.row * TILE_SIZE + TILE_SIZE / 2};
}

Rectangle map_get_tile_bounds(GridPosition position) {
  Vector2 tile = map_grid_to_world(position);
  return (Rectangle){tile.x, tile.y, TILE_SIZE, TILE_SIZE};
}
