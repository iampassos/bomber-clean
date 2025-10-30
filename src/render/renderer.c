#include "renderer.h"
#include "core/asset_manager.h"
#include "entities/entities_manager.h"
#include "entities/entity.h"
#include "game/game_manager.h"
#include "map_renderer.h"
#include <raylib.h>

void renderer_draw_game() {
  map_renderer();
  renderer_hud();

  entities_manager_draw_all_layer(LAYER_BOMBS);
  entities_manager_draw_all_layer(LAYER_PLAYERS);

  if (game_manager.view_mode == VIEW_DEBUG) {
    map_renderer_debug();
    entities_manager_debug_all();
  }
}

void renderer_hud() {
  DrawTexture(*asset_manager_get_hud_texture(), 0, 0, WHITE);
}
