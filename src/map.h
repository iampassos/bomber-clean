#ifndef MAP_H
#define MAP_H

#include <common.h>
#include <raylib.h>

typedef enum { MAP_BATTLE_STAGE_1, MAP_STAGE_1 } MapType;

typedef enum {
  TILE_EMPTY,
  TILE_WALL,
  TILE_BRICK,
} TileType;

extern const Color TILE_COLORS[3];

typedef struct GridPosition {
  int col;
  int row;
} GridPosition;

typedef struct Map {
  TileType grid[GRID_HEIGHT][GRID_WIDTH];
  MapType stage;
  int bomb_animation_steps;
  void (*draw)(void);
  void (*update)(void);
} Map;

GridPosition map_get_grid_position(Vector2 position);
Vector2 map_get_vector_from_grid_center(GridPosition position);
Vector2 map_get_vector_from_grid(GridPosition position);
void map_init(MapType type);

void map_load(void (*func)(void));
void map_update(void (*func)(void));
void map_draw(void (*func)(void));

void map_load_battle_stage_one();
void map_update_battle_stage_one();
void map_draw_battle_stage_one();

void map_load_stage_one();
void map_update_stage_one();
void map_draw_stage_one();

#endif
