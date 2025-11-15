#ifndef MAP_H
#define MAP_H

#include "common.h"
#include <raylib.h>

typedef enum {
  MAP_NORMAL_ZONE,
  MAP_JUMP_ZONE,
  MAP_BELT_ZONE,
  MAP_WESTERN_ZONE,
  MAP_BOMB_ZONE,
  MAP_DUEL_ZONE,
  MAP_SPEED_ZONE,
  MAP_LIGHT_ZONE,
} MapType;

// tipos de estruturasd do mapa
typedef enum {
  TILE_EMPTY,
  TILE_WALL,
  TILE_BRICK,
} TileType;

//representação de um grid position
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

Map *map_create(MapType map_type); // cria o mapa com a probabilidade dos bricks
Map *map_next(Map *map);
Map *map_first();

TileType map_get_tile(Map *map, GridPosition position);
void map_set_tile(Map *map, GridPosition position, TileType tile); //Altera o tipo de tile de uma posição do map
bool map_is_walkable(Map *map, GridPosition position); //Verifica se a posição é caminhável (tile vazio)
bool map_is_same_grid(GridPosition grid1, GridPosition grid2); //Compara duas posições no grid
bool map_is_valid_grid(GridPosition grid); //Verifica se a posição está dentro dos limites do grid
bool map_is_valid_position(Vector2 position); // Verifica o pixel estra dentro dos limites do mapa

GridPosition map_world_to_grid(Vector2 position); //converte pixel em posição de grid no mapa
Vector2 map_grid_to_world(GridPosition position); 
Vector2 map_grid_to_world_center(GridPosition position);
Rectangle map_get_tile_bounds(GridPosition position);

#endif
