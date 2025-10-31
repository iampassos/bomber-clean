#include "game_manager.h"
#include "core/asset_manager.h"
#include "core/map.h"
#include "entities/entities_manager.h"
#include "entities/explosion_tile.h"
#include "input/input_manager.h"
#include "render/map_renderer.h"
#include <raylib.h>

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
  GridPosition affected_center = center;

  GridPosition affected_up[4 * GRID_WIDTH] = {0};
  GridPosition affected_down[4 * GRID_WIDTH] = {0};
  GridPosition affected_left[4 * GRID_WIDTH] = {0};
  GridPosition affected_right[4 * GRID_WIDTH] = {0};

  GridPosition destroyed[4 * GRID_WIDTH] = {0};

  int affected_length_up = 0;
  int affected_length_down = 0;
  int affected_length_left = 0;
  int affected_length_right = 0;

  int destroyed_length = 0;

  // 0 = up, 1 = down, 2 = left, 3 = right
  int row_direction[4] = {-1, 1, 0, 0};
  int col_direction[4] = {0, 0, -1, 1};

  for (int i = 0; i < 4; i++) {
    for (int j = 1; j <= radius; j++) {

      int row = center.row + row_direction[i] * j;
      int col = center.col + col_direction[i] * j;

      GridPosition new_grid_position = {col, row};
      TileType tile = map_get_tile(&game_manager.map, new_grid_position);

      if (tile == TILE_EMPTY) {
        if (i == 0)
          affected_up[affected_length_up++] = new_grid_position;
        else if (i == 1)
          affected_down[affected_length_down++] = new_grid_position;
        else if (i == 2)
          affected_left[affected_length_left++] = new_grid_position;
        else if (i == 3)
          affected_right[affected_length_right++] = new_grid_position;
      } else if (tile == TILE_BRICK) {
        destroyed[destroyed_length++] = new_grid_position;
        break;
      } else {
        break;
      }
    }
  }

  for (int i = 0; i < destroyed_length; i++) {
    map_set_tile(&game_manager.map, destroyed[i], TILE_EMPTY);
    map_renderer_animate_brick_destruction(destroyed[i]);
  }

  // empty animetion
  explosion_tile_create(map_grid_to_world(center));

  for (int i = 0; i < affected_length_up; i++)
    explosion_tile_create(map_grid_to_world(affected_up[i]));

  for (int i = 0; i < affected_length_down; i++)
    explosion_tile_create(map_grid_to_world(affected_down[i]));

  for (int i = 0; i < affected_length_left; i++)
    explosion_tile_create(map_grid_to_world(affected_left[i]));

  for (int i = 0; i < affected_length_right; i++)
    explosion_tile_create(map_grid_to_world(affected_right[i]));
}
