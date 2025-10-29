#ifndef BOMB_H
#define BOMB_H

#include "common.h"
#include <map.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BOMBS 50
#define EXPLODE_DELAY 2.0f
#define PLUS_EXPLODE_DELAY 5.0f


extern GridPosition
    bomb_validedd_position_in_grid[GRID_SIZE]; // vetor com todas as posições
                                               // possíveis para bombas

typedef struct {
  GridPosition grid_position;
  int explosion_radius;
  double spawn_time;
  int animation_step;
  float last_animation_step;
} Bomb;

typedef struct {
  Bomb bombs[MAX_BOMBS];
  int current_length;
} Bombs;


void bomb_insert(Bombs *array, GridPosition pos);
void bomb_clear_all(Bombs *array);
void bomb_remove_per_idx(Bombs *array, int idx_remove);
Bomb *bomb_find_idx(Bombs *array, int idx);
bool bomb_remove_by_grid_position(GridPosition pos);
Bomb *bomb_find_on_grid_position(GridPosition pos);
void bombs_increase_time_to_explode(Bombs *array);
int bomb_find_to_explode(Bombs *array);
void bombs_update_all();

// Funções para spawn de bombas
// void bomb_dfs(GridPosition pos, TileType grid[GRID_HEIGHT][GRID_WIDTH], int
// visited[GRID_HEIGHT][GRID_WIDTH]);
int bomb_get_spawnable_positions(GridPosition *bomb_validedd_position_in_grid,
                                 GridPosition player_position,
                                 TileType grid[GRID_HEIGHT][GRID_WIDTH]);

#endif
