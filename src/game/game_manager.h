#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "core/common.h"
#include "core/map.h"
#include "enemies/enemy.h"
#include "entities/player.h"
#include "entities/power_up.h"

typedef struct {
  Map *map;
  float dt;
  Player *players[MAX_PLAYERS];
  int player_count;
  float last_event_interval;
  float event_interval;
  float stage_start;
  float game_start;
  int bomb_radius;
  int bomb_quantity;
  int enemy_quantity;
  EnemyType enemies_available[1];
  int enemies_available_n;
  bool debug;
  bool hitboxes;
  bool grid;
  bool fullscreen;
  bool fps;
} GameManager;

extern GameManager game_manager;

void game_manager_init();
void game_manager_update(float dt);

void game_manager_start_stage();
void game_manager_random_interval();

void game_manager_on_next_stage();
void game_manager_on_enemy_touch(Player *player, Enemy *enemy);
void game_manager_on_entity_exploded(Entity *entity);
void game_manager_on_bomb_exploded(GridPosition center, int radius,
                                   int player_id);
void game_manager_on_explosion_end(GridPosition grid);
void game_manager_on_power_up_press(Player *player, PowerUp *power_up);

int weighted_average(int items, float probabilities[]);

#endif
