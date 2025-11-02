#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "core/common.h"
#include "core/map.h"
#include "entities/player.h"
#include "entities/power_up.h"

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

void game_manager_on_entity_exploded(Entity *entity);
void game_manager_on_bomb_exploded(GridPosition center, int radius);
void game_manager_on_power_up_press(Player *player, PowerUp *power_up);

int weighted_average(int items, float probabilities[]);

#endif
