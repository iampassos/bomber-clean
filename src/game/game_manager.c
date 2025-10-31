#include "game_manager.h"
#include "core/asset_manager.h"
#include "core/map.h"
#include "entities/entities_manager.h"
#include "entities/explosion_tile.h"
#include "input/input_manager.h"
#include "render/map_renderer.h"
#include "rules.h"
#include <raylib.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

GameManager game_manager = {0};

void game_manager_init() {}

void game_manager_update(float dt) {
  for (int i = 0; i < game_manager.player_count; i++) {
    PlayerInput input = input_manager_get_player_input(i);

    input.place_bomb = input.place_bomb &&
                       GetTime() - input_manager.last_bomb_input[i] >= 0.25f;
    input_manager.last_bomb_input[i] =
        input.place_bomb ? GetTime() : input_manager.last_bomb_input[i];

    game_manager.players[i]->input = input;

    game_manager.view_mode =
        input.debug && GetTime() - input_manager.last_view_input[i] >= 0.25f
            ? game_manager.view_mode == VIEW_NORMAL ? VIEW_DEBUG : VIEW_NORMAL
            : game_manager.view_mode;
    input_manager.last_view_input[i] =
        input.debug ? GetTime() : input_manager.last_view_input[i];
  }

  entities_manager_update_all();
}

void game_manager_start_stage() {
  map_init(&game_manager.map, MAP_STAGE_1);
  asset_manager_load_map_textures(game_manager.map.stage);
  game_manager.players[game_manager.player_count] =
      player_create(0, (Vector2){0, 0});
  game_manager.player_count++;
}

void game_manager_on_bomb_exploded(GridPosition center, int radius) {
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
      TileType tile = map_get_tile(&game_manager.map, new_grid_position);

      if (tile == TILE_EMPTY) {
        affected[affected_length++] = new_grid_position;
      } else if (tile == TILE_BRICK) {
        destroyed[destroyed_length++] = new_grid_position;
        break;
      } else {
        break;
      }
    }
  }

  explosion_tile_create(map_grid_to_world(affected[0]), DIR_DOWN, true);

  for (int i = 1; i < affected_length; i++) {
    if (affected[i].row == center.row) {
      explosion_tile_create(map_grid_to_world(affected[i]),
                            affected[i].col > center.col ? DIR_RIGHT : DIR_LEFT,
                            false);
    } else {
      explosion_tile_create(map_grid_to_world(affected[i]),
                            affected[i].row > center.row ? DIR_UP : DIR_DOWN,
                            false);
    }
  }

  for (int i = 0; i < destroyed_length; i++) {
    map_set_tile(&game_manager.map, destroyed[i], TILE_EMPTY);
    map_renderer_animate_brick_destruction(destroyed[i]);
  }

  for (int i = 0; i < entities_manager.count; i++) {
    Entity *entity = entities_manager.entries[i];

    if (entity->type != ENTITY_EXPLOSION_TILE) {
      if (entity->type == ENTITY_PLAYER &&
          rules_can_kill_player((Player *)entity)) {
        Player *player = (Player *)entity;
        player->alive = false;
      }
    }
  }

  srand(time(NULL));
  int spawn = rand() % 100 < 100;

  if (spawn) {
    srand(time(NULL));
    power_up_create(map_grid_to_world(center), rand() % 3);
  }
}

void game_manager_on_power_up_press(Player *player, PowerUp *power_up) {
  if (!rules_player_can_consume_power_up(player, power_up))
    return;

  switch (power_up->power_up_type) {
  case POWER_UP_LIFE:
    player->lives++;
    break;
  case POWER_UP_SPEED:
    player->speed = fmin(MAX_PLAYER_SPEED, player->speed + POWER_UP_SPEED_INCREASE);
    break;
  case POWER_UP_BOMB:
    player->bomb_capacity++;
    break;
  }

  entities_manager_remove((Entity *)power_up);
}
