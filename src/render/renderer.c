#include "renderer.h"
#include "core/assets/asset_manager.h"
#include "core/common.h"
#include "entities/entities_manager.h"
#include "entities/entity.h"
#include "game/game_manager.h"
#include "map_renderer.h"
#include <raylib.h>

void renderer_draw_game() {
  map_renderer();
  renderer_hud();

  entities_manager_draw_all_layer(LAYER_POWER_UPS);
  entities_manager_draw_all_layer(LAYER_BOMBS);
  entities_manager_draw_all_layer(LAYER_ENEMIES);
  entities_manager_draw_all_layer(LAYER_PLAYERS);

  if (game_manager.debug) {
    entities_manager_debug_all();
    entities_manager_debug();
  }
  if (game_manager.hitboxes)
    entities_manager_hitboxes();
  if (game_manager.grid) {
    map_renderer_debug();
    entities_manager_grid();
  }
}

void renderer_hud() {
  DrawTexture(*asset_manager_get_hud_texture(), MAP_X_OFFSET - TILE_SIZE / 2.0f,
              0, WHITE);
}
