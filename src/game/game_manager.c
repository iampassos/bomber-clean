#include "game_manager.h"
#include "core/asset_manager.h"
#include "entities/entities_manager.h"
#include "input/input_manager.h"
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
