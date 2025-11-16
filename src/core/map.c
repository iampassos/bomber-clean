#include "map.h"
#include "core/common.h"
#include "enemies/enemy.h"
#include "linked_list.h"
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <wchar.h>

LinkedList *maps_linked_list = NULL;

Map *map_create(MapType map_type) {
  if (maps_linked_list == NULL)
    maps_linked_list = list_create();

  Map *map = malloc(sizeof(Map));

  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      if (i == 0 || j == 0 || i + 1 == GRID_HEIGHT || j + 1 == GRID_WIDTH ||
          (i % 2 == 0 && j % 2 == 0)) {
        map->grid[i][j] = TILE_WALL;
      } else
        map->grid[i][j] =
            (i != 1 || j != 1) &&
                    rand() % 100 <
                        (CLEAN_MODE ? 0 : PROBABILITY_SPAWN_TILE_BRICK_ON_MAP)
                ? TILE_BRICK
                : TILE_EMPTY;
    }
  }

  // garantir que tenha laterais empyt no spawn do bomber man
  // PLAYER 1 (canto superior esquerdo)
  map->grid[1][1] = TILE_EMPTY;
  map->grid[1][2] = TILE_EMPTY;
  map->grid[2][1] = TILE_EMPTY;

  // PLAYER 2 (canto superior direito)
  map->grid[1][12] = TILE_EMPTY;
  map->grid[1][13] = TILE_EMPTY;
  map->grid[2][13] = TILE_EMPTY;

  // PLAYER 3 (canto inferior esquerdo)
  map->grid[10][1] = TILE_EMPTY;
  map->grid[11][1] = TILE_EMPTY;
  map->grid[11][2] = TILE_EMPTY;

  // PLAYER 4 (canto inferior direito)
  map->grid[10][13] = TILE_EMPTY;
  map->grid[11][12] = TILE_EMPTY;
  map->grid[11][13] = TILE_EMPTY;

  map->stage = map_type;

  map->enemies_n = 0;
  switch (map_type) {
  case MAP_NORMAL_ZONE:
    break;
  default:
    map->enemies[map->enemies_n++] = ENEMY_BALLOM;
    break;
  }

  list_insert_end(maps_linked_list, map); // inseri na lista encadeada

  return map;
}

Map *map_first() {
  Map *m = (Map *)list_get_data_position(maps_linked_list, 0);
  return m != NULL ? m : NULL;
}

Map *map_next(Map *map) {
  int pos = list_find_node_position(maps_linked_list, map);
  Map *next = (Map *)list_get_data_position(maps_linked_list, pos + 1);
  if (next != NULL) {
    list_remove_node(maps_linked_list, map);
    return next;
  }
  return NULL;
}

void map_clean_up() { list_free_all(&maps_linked_list); }

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
