#ifndef MAP_H
#define MAP_H

#include <common.h>
#include <raylib.h>

typedef enum { FIRST } Stage;

typedef enum {
  TILE_EMPTY,
  TILE_WALL,
  TILE_BRICK,
} TileType;

extern const Color TILE_COLORS[3];

typedef struct Map {
  TileType grid[GRID_HEIGHT][GRID_WIDTH];
  Stage stage;
  void (*draw)(void);
} Map;

void map_init();
void map_load(void (*func)(void));
void map_load_first();
void map_draw(void (*func)(void));
void map_draw_first();

#endif
