#include "renderer.h"
#include "core/asset_manager.h"
#include "core/common.h"
#include <raylib.h>

void renderer_draw_game() {
  renderer_map_background();
  renderer_hud();
}

void renderer_map_background() {
  DrawTexture(*asset_manager_get_map_background_texture(),
              MAP_X_OFFSET - TILE_SIZE, MAP_Y_OFFSET, WHITE);
}

void renderer_hud() {
  DrawTexture(*asset_manager_get_hud_texture(), 0, 0, WHITE);
}
