#include "game_manager.h"
#include "core/assets/assets_maps.h"
#include "core/common.h"
#include "core/map.h"
#include "enemies/ballom.h"
#include "enemies/enemy.h"
#include "entities/bomb.h"
#include "entities/entities_manager.h"
#include "entities/entity.h"
#include "entities/explosion_tile.h"
#include "entities/player.h"
#include "entities/power_up.h"
#include "input/input_manager.h"
#include "render/map_renderer.h"
#include "rules.h"
#include <math.h>
#include <raylib.h>
#include <stdlib.h>

GameManager game_manager = {0};

void game_manager_init() {
  game_manager.player_count = 0;
  game_manager.stage_start = 0;
  game_manager.last_event_interval = GetTime();
  game_manager.bomb_radius = RANDOM_BOMB_INITIAL_RADIUS;
  game_manager.bomb_quantity = RANDOM_BOMB_INITIAL_QUANTITY;
  game_manager.event_interval = RANDOM_EVENT_INTERVAL;
  game_manager.enemy_quantity = RANDOM_ENEMY_INITIAL_QUANTITY;
  game_manager.enemies_available_n = 0;

  game_manager.map = map_create(MAP_BATTLE_STAGE_1);
  map_create(MAP_PEACE_TOWN);

  GridPosition spawn_pos[4] = {{1, 1}, {13, 11}, {13, 1}, {1, 11}};

  do {
    game_manager.players[game_manager.player_count] = player_create(
        game_manager.player_count, spawn_pos[game_manager.player_count]);
    game_manager.player_count++;
  } while (game_manager.player_count < input_manager.controllers_n);

  game_manager_start_stage();
}

void game_manager_update(float dt) {
  for (int i = 0; i < game_manager.player_count; i++) {
    PlayerInput input = input_manager_get_player_input(i);

    input.place_bomb =
        input.place_bomb && GetTime() - input_manager.last_input[i] >= 0.25f;

    input_manager.last_input[i] =
        input.place_bomb ? GetTime() : input_manager.last_input[i];

    game_manager.players[i]->input = input;

    game_manager.view_mode =
        input.debug && GetTime() - input_manager.last_input[i] >= 0.25f
            ? game_manager.view_mode == VIEW_NORMAL ? VIEW_DEBUG : VIEW_NORMAL
            : game_manager.view_mode;

    input_manager.last_input[i] =
        input.debug ? GetTime() : input_manager.last_input[i];
  }

  game_manager_random_interval();
  entities_manager_update_all();

  if (GetTime() - game_manager.stage_start >= MAP_CHANGE_INTERVAL)
    game_manager_on_next_stage();
}

void game_manager_start_stage() {
  for (int i = 0; i < game_manager.player_count; i++) {
    Player *player = game_manager.players[i];
    player->entity.position = entity_grid_to_world(
        &player->entity, player->spawn_grid, PLAYER_HEIGHT_TOLERANCE);
  }

  assets_maps_load_textures(game_manager.map->stage);

  game_manager.stage_start = GetTime();

  for (int i = 0; i < game_manager.map->enemies_n; i++) {
    game_manager.enemies_available[game_manager.enemies_available_n++] =
        game_manager.map->enemies[i];
  }

  // ballom_create((GridPosition){1, 1});
}

void game_manager_on_next_stage() {
  Map *next = map_next(game_manager.map);

  if (!next)
    return;

  entities_manager_clear_but_player();

  game_manager.map = next;
  game_manager_start_stage();

  game_manager.bomb_radius += RANDOM_BOMB_RADIUS_INCREASE;
  game_manager.bomb_quantity +=
      game_manager.map->stage % RANDOM_BOMB_MAP_QUANTITY_INCREASE == 0
          ? RANDOM_BOMB_QUANTITY_INCREASE
          : 0;
  game_manager.enemy_quantity +=
      game_manager.map->stage % RANDOM_ENEMY_MAP_QUANTITY_INCREASE == 0
          ? RANDOM_ENEMY_QUANTITY_INCREASE
          : 0;
}

void game_manager_on_enemy_touch(Player *player) {
  if (rules_can_kill_player(player))
    player->alive = false;
}

void game_manager_on_entity_exploded(Entity *entity) {
  GridPosition pos = entity_world_to_grid(entity, entity->height_tolerance);

  if (explosion_tile_at_grid(pos) == NULL)
    return;

  switch (entity->type) {
  case ENTITY_PLAYER:
    Player *player = (Player *)entity;
    if (rules_can_kill_player(player))
      player->alive = false;
    break;
  case ENTITY_POWER_UP:
    PowerUp *power_up = (PowerUp *)entity;
    if (rules_can_kill_power_up(power_up))
      power_up->active = false;
    break;
  case ENTITY_ENEMY:
    Enemy *enemy = (Enemy *)entity;
    if (rules_can_kill_enemy(enemy))
      enemy->alive = false;
    break;
  default:
    break;
  }
}

void game_manager_on_bomb_exploded(GridPosition center, int radius,
                                   int player_id) {
  GridPosition affected[4 * GRID_WIDTH] = {0};
  GridPosition destroyed[4 * GRID_WIDTH] = {0};

  int affected_length = 0;
  int destroyed_length = 0;

  // 0 = up, 1 = down, 2 = left, 3 = right
  int row_direction[4] = {-1, 1, 0, 0};
  int col_direction[4] = {0, 0, -1, 1};

  affected[affected_length++] = center; // idx = 0 center

  for (int i = 0; i < 4; i++) {
    for (int j = 1; j <= radius; j++) {

      int row = center.row + row_direction[i] * j;
      int col = center.col + col_direction[i] * j;

      GridPosition new_grid_position = {col, row};
      TileType tile = map_get_tile(game_manager.map, new_grid_position);

      if (tile == TILE_EMPTY) {
        if (bomb_at_grid(new_grid_position) ||
            explosion_tile_at_grid(new_grid_position)) {
          destroyed[destroyed_length++] = new_grid_position;
          break;
        } else
          affected[affected_length++] = new_grid_position;
      } else if (tile == TILE_BRICK) {
        destroyed[destroyed_length++] = new_grid_position;
        break;
      } else {
        break;
      }
    }
  }

  explosion_tile_create(player_id, map_grid_to_world(affected[0]), DIR_DOWN,
                        EXPLOSION_CENTER);

  for (int i = 1; i < affected_length; i++) {
    if (affected[i].row == center.row) {
      explosion_tile_create(player_id, map_grid_to_world(affected[i]),
                            affected[i].col > center.col ? DIR_RIGHT : DIR_LEFT,
                            affected[i].col == center.col + radius ||
                                    affected[i].col == center.col - radius
                                ? EXPLOSION_FINAL
                                : EXPLOSION_MIDDLE);
    } else {
      explosion_tile_create(player_id, map_grid_to_world(affected[i]),
                            affected[i].row < center.row ? DIR_UP : DIR_DOWN,
                            affected[i].row == center.row + radius ||
                                    affected[i].row == center.row - radius
                                ? EXPLOSION_FINAL
                                : EXPLOSION_MIDDLE);
    }
  }

  for (int i = 0; i < destroyed_length; i++) {
    map_set_tile(game_manager.map, destroyed[i], TILE_EMPTY);
    if (!bomb_at_grid(destroyed[i]) && !explosion_tile_at_grid(destroyed[i]))
      map_renderer_animate_brick_destruction(destroyed[i]);
  }

  for (int i = 0; i < entities_manager.count; i++) {
    Entity *entity = entities_manager.entries[i];
    game_manager_on_entity_exploded(entity);
  }
}

void game_manager_on_explosion_end(GridPosition grid) {
  if (rules_can_spawn_power_up(grid)) {
    int spawn = rand() % 100 < POWER_UP_PROBABILITY;

    if (spawn) {
      float probabilities[6] = {2.5f, 27.5f, 27.5f, 27.5f, 1.0f, 14};
      power_up_create(map_grid_to_world(grid),
                      weighted_average(6, probabilities));
    }
  }
}

void game_manager_on_power_up_press(Player *player, PowerUp *power_up) {
  if (rules_player_can_consume_power_up(player, power_up)) {
    switch (power_up->power_up_type) {
    case POWER_UP_LIFE:
      player->lives++;
      break;
    case POWER_UP_SPEED:
      player->speed =
          fmin(MAX_PLAYER_SPEED, player->speed + POWER_UP_SPEED_INCREASE);
      break;
    case POWER_UP_BOMB:
      player->bomb_capacity++;
      break;
    case POWER_UP_RADIUS:
      player->bomb_radius++;
      break;
    case POWER_UP_MAXIMUM_RADIUS:
      player->bomb_radius = MAX_BOMB_RADIUS;
      break;
    case POWER_UP_INVENCIBLE:
      player->invencible = true;
      player->invencibility_start = GetTime();
      break;
    }
  }

  entities_manager_remove((Entity *)power_up);
}

void game_manager_random_interval() {
  if (GetTime() - game_manager.last_event_interval >=
      game_manager.event_interval) {
    game_manager.last_event_interval = GetTime();

    float probabilities[] = {ENEMY_PROBABILITY, BOMB_PROBABILITY};
    int ev = weighted_average(2, probabilities);

    if (ev == 0) {
      for (int i = 0, tries = 0; i < game_manager.enemy_quantity && tries < 10;
           i++) {
        int col = 1 + rand() % (GRID_HEIGHT - 2); // 1 a 11
        int row = 1 + rand() % (GRID_WIDTH - 2);  // 1 a 13
        GridPosition grid = {col, row};

        if (rules_can_spawn_enemy(grid)) {
          switch (rand() % game_manager.enemies_available_n) {
          case ENEMY_BALLOM:
            ballom_create(grid);
            break;
          }
          tries = 0;
        } else {
          tries++;
          i--;
        }
      }
    } else {
      for (int i = 0, tries = 0; i < game_manager.bomb_quantity && tries < 10;
           i++) {
        int col = 1 + rand() % (GRID_HEIGHT - 2); // 1 a 11
        int row = 1 + rand() % (GRID_WIDTH - 2);  // 1 a 13
        GridPosition grid = {col, row};

        if (rules_can_spawn_bomb(grid)) {
          bomb_create(-1, map_grid_to_world(grid), game_manager.bomb_radius);
          tries = 0;
        } else {
          tries++;
          i--;
        }
      }
    }
  }
}

int weighted_average(int items, float *probabilities) {
  float cumulative[items];
  cumulative[0] = probabilities[0];
  for (int i = 1; i < items; i++)
    cumulative[i] = cumulative[i - 1] + probabilities[i];

  float r = ((float)rand() / RAND_MAX) * cumulative[items - 1];

  for (int i = 0; i < items; i++) {
    if (r < cumulative[i]) {
      return i;
    }
  }

  return -1;
}
