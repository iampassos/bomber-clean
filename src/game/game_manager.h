#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "core/common.h"
#include "core/map.h"
#include "entities/player.h"

typedef enum { VIEW_NORMAL, VIEW_DEBUG } ViewMode;

typedef struct {
  Map map;
  Player *players[MAX_PLAYERS];
  int player_count;
  ViewMode view_mode;
} GameManager;

extern GameManager game_manager;

void game_manager_init();
void game_manager_update(float dt);

void game_manager_start_stage();

#endif
