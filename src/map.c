#include "map.h"
#include <stdlib.h>

const Color TILE_COLORS[3] = {
    [TILE_EMPTY] = (Color){17, 92, 51, 255},
    [TILE_WALL] = (Color){101, 101, 101, 255},
    [TILE_BRICK] = (Color){58, 58, 58, 255},
};

Map *map_init() {
  Map *map = malloc(sizeof(Map));

  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      if (i == 0 || j == 0 || i + 1 == GRID_HEIGHT || j + 1 == GRID_WIDTH ||
          (i % 2 == 0 && j % 2 == 0))
        map->grid[i][j] = TILE_WALL;
      else
        map->grid[i][j] = TILE_EMPTY;
    }
  }

  return map;
}
