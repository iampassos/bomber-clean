#ifndef BOMB_H
#define BOMB_H

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map.h>  // Dependência usada para TileType

// Constantes
#define EXPLODE_DELAY 5.0
#define PLUS_EXPLODE_DELAY 5.0

// Estruturas
typedef struct Bomb {
    int col;
    int row;
    double spawnTime;
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
void bomb_insert(Bombs *list, int col, int row);
void bomb_remove(Bombs *list);
bool bomb_node_remove(Bombs *list, Bomb *node);
void bomb_free_list(Bombs *list);
bool bomb_is_possible_insert_in_map(Bombs *list,int col, int row, TileType tile);
Bomb *bomb_find_to_explode(Bombs *list);
void bombs_increase_time_to_explode(Bombs *list);

#endif
