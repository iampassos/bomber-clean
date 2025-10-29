#include "bomb.h"
#include "animation.h"
#include "state.h"

void bomb_insert(Bombs *array, GridPosition pos) {
  if (array->current_length >= MAX_BOMBS)
    return;

  Bomb newBomb;
  newBomb.grid_position = pos;
  newBomb.explosion_radius = 3; // Por hora fixo como 3 Grid de explosao
  newBomb.spawn_time = GetTime();
  newBomb.animation =
      animation_new(3, EXPLODE_DELAY / 10.0f, 1, NULL, NULL, NULL);
  array->bombs[(array->current_length)++] = newBomb;
}

void bomb_clear_all(Bombs *array) { array->current_length = 0; }

void bomb_remove_per_idx(Bombs *array, int idx_remove) {
  if (idx_remove < 0 || idx_remove >= array->current_length)
    return;

  for (int i = idx_remove; i < array->current_length - 1; i++) {
    array->bombs[i] = array->bombs[i + 1];
  }
  array->current_length--;
}

Bomb *bomb_find_idx(Bombs *array, int idx) {
  if (idx < 0 || idx >= array->current_length)
    return NULL;
  return &array->bombs[idx];
}

bool bomb_remove_by_grid_position(GridPosition pos) {
  for (int i = 0; i < state.players.count; i++) {
    Bombs *array = &state.bombs[i];
    for (int j = 0; j < array->current_length; j++) {
      if (array->bombs[j].grid_position.col == pos.col &&
          array->bombs[j].grid_position.row == pos.row) {
        bomb_remove_per_idx(array, j);
        return true;
      }
    }
  }

  return false;
}

Bomb *bomb_find_on_grid_position(GridPosition pos) {
  for (int i = 0; i < state.players.count; i++) {
    Bombs *array = &state.bombs[i];
    for (int j = 0; j < array->current_length; j++) {
      if (array->bombs[j].grid_position.col == pos.col &&
          array->bombs[j].grid_position.row == pos.row)
        return &array->bombs[j];
    }
  }

  return NULL;
}

void bombs_increase_time_to_explode(Bombs *array) {
  for (int i = 0; i < array->current_length; i++) {
    array->bombs[i].spawn_time += PLUS_EXPLODE_DELAY;
  }
}

int bomb_find_to_explode(Bombs *array) {
  for (int i = 0; i < array->current_length; i++) {
    if (GetTime() - array->bombs[i].spawn_time >= EXPLODE_DELAY)
      return i;
  }

  return -1;
}

void bombs_update_all() {
  for (int i = 0; i < state.players.count; i++) {
    Bombs *array = &state.bombs[i];
    int idx = bomb_find_to_explode(array);

    if (idx != -1)
      bomb_remove_per_idx(array, idx);

    for (int i = 0; i < array->current_length; i++)
      animation_update(&array->bombs[i].animation);
  }
}

// DFS

void bomb_dfs(GridPosition pos, TileType grid[GRID_HEIGHT][GRID_WIDTH],
              int visited[GRID_HEIGHT][GRID_WIDTH]) {
  if (pos.col < 0 || pos.col >= GRID_WIDTH || pos.row < 0 ||
      pos.row >= GRID_HEIGHT)
    return;

  if (visited[pos.row][pos.col] == 1 || grid[pos.row][pos.col] != TILE_EMPTY)
    return;

  visited[pos.row][pos.col] = 1;

  bomb_dfs((GridPosition){pos.col + 1, pos.row}, grid, visited); // direita
  bomb_dfs((GridPosition){pos.col - 1, pos.row}, grid, visited); // esquerda
  bomb_dfs((GridPosition){pos.col, pos.row + 1}, grid, visited); // baixo
  bomb_dfs((GridPosition){pos.col, pos.row - 1}, grid, visited); // cima
}

int bomb_get_spawnable_positions(GridPosition *bomb_validedd_position_in_grid,
                                 GridPosition player_position,
                                 TileType grid[GRID_HEIGHT][GRID_WIDTH]) {
  int visited[GRID_HEIGHT][GRID_WIDTH] = {0};

  bomb_dfs(player_position, grid, visited);

  int count = 0;
  for (int row = 0; row < GRID_HEIGHT; row++) {
    for (int col = 0; col < GRID_WIDTH; col++) {
      if (row == player_position.row && col == player_position.col)
        continue;
      if (visited[row][col] == 1)
        bomb_validedd_position_in_grid[count++] = (GridPosition){col, row};
    }
  }
  return count;
}