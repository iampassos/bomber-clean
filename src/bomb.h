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
    Vector2 posi;
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
void create_bombs_list(Bombs *list);
void insert_bomb(Bombs *list, Vector2 posi);
void remove_bomb(Bombs *list);
bool remove_node_bomb(Bombs *list, Bomb *node);
void free_list(Bombs *list);
bool is_possible_insert_bomb_in_map(Bombs *list, Vector2 spawn_posi, TileType tile);
Bomb *find_bomb_to_explode(Bombs *list);
void increase_time_to_explode_bombs(Bombs *list);

#endif
