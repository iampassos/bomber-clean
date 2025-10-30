#include "game_manager.h"
#include "entities/entities_manager.h"
#include "render/input_manager.h"

GameManager game_manager = {0};

void game_manager_init() {}

void game_manager_update() {
  game_manager.players[0].input = input_manager.player_inputs[0];
  entities_manager_update_all();
}
