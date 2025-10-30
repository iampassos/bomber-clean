#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "core/map.h"
#include "entities/player.h"

typedef struct {
  Map map;
  Player players[4];
  int player_count;
} GameManager;

extern GameManager game_manager;

void game_manager_init();

#endif
