#include "game_manager.h"
#include "core/asset_manager.h"
#include "entities/entities_manager.h"
#include "entities/explosion_tile.h"
#include "input/input_manager.h"
#include <math.h>
#include <raylib.h>
#include <string.h>

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

  TileType center_tile = map_get_tile(&game_manager.map, center);

  affected[affected_length++] = center;

  int directions[4][2] = {
      {0, 1},  // up
      {0, -1}, // down
      {-1, 0}, // left
      {1, 0}   // right
  };

  for (int d = 0; d < 4; d++) {
    int dx = directions[d][0]; // coluna up or down
    int dy = directions[d][1]; // linha  left or right

    for (int i = 1; i <= radius; i++) {
      GridPosition new = {center.col + dx * i, center.row + dy * i};

      TileType tile = map_get_tile(&game_manager.map, new);

      if (tile == TILE_EMPTY) {
        affected[affected_length++] = new;
      } else if (tile == TILE_BRICK) {
        destroyed[destroyed_length++] = new;
        break;
      } else {
        break;
      }
    }
  }

  for (int i = 0; i < destroyed_length; i++)
    map_set_tile(&game_manager.map, destroyed[i], TILE_EMPTY);

  for (int i = 0; i < affected_length; i++)
    explosion_tile_create(map_grid_to_world(affected[i]));
}