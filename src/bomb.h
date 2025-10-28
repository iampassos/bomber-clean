#ifndef BOMB_H
#define BOMB_H

#include <map.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constantes
#define EXPLODE_DELAY 2.0f
#define PLUS_EXPLODE_DELAY 5.0f

// Estruturas
typedef struct Bomb {
  GridPosition grid_position;
  double spawnTime;
  int animation_step;
  float last_animation_step;
  struct Bomb *next;
  struct Bomb *prev;
} Bomb;

typedef struct Bombs {
  struct Bomb *head;
  struct Bomb *tail;
  int currentLength;
  int totalCreated;
} Bombs;

// Funções principais
void bombs_create_list(Bombs *list);
void bomb_insert(Bombs *list, GridPosition pos);
void bomb_remove(Bombs *list);
bool bomb_node_remove(Bombs *list, Bomb *node);
void bomb_free_list(Bombs *list);
bool bomb_is_possible_insert_in_map(Bombs *list, GridPosition pos,
                                    TileType tile);
Bomb *bomb_find_on_grid_position(GridPosition pos);
Bomb *bomb_find_n(Bombs *list, int n);
Bomb *bomb_find_to_explode(Bombs *list);
void bombs_increase_time_to_explode(Bombs *list);
void bombs_update_all();

#endif
