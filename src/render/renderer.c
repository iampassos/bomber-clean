#include "renderer.h"
#include "core/asset_manager.h"
#include "core/common.h"
#include "core/map.h"
#include "entities/entities_manager.h"
#include "game/game_manager.h"
#include <raylib.h>
#include <stdio.h>

void renderer_draw_game() {
  renderer_map_background();
  renderer_hud();
  entities_manager_draw_all();
  renderer_map_debug();
}

void renderer_map_background() {
  DrawTexture(*asset_manager_get_map_background_texture(),
              MAP_X_OFFSET - TILE_SIZE, MAP_Y_OFFSET, WHITE);
}

void renderer_map_debug() {
  for (int i = 0; i <= GRID_WIDTH; i++)
    DrawLine(MAP_X_OFFSET + i * TILE_SIZE, MAP_Y_OFFSET,
             MAP_X_OFFSET + i * TILE_SIZE,
             MAP_Y_OFFSET + GRID_HEIGHT * TILE_SIZE, WHITE);

  for (int i = 0; i < GRID_HEIGHT; i++)
    DrawLine(MAP_X_OFFSET, MAP_Y_OFFSET + i * TILE_SIZE,
             MAP_X_OFFSET + TILE_SIZE * GRID_WIDTH,
             MAP_Y_OFFSET + i * TILE_SIZE, WHITE);

  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      Vector2 center = map_grid_to_world_center((GridPosition){j, i});
      char buff[3];
      snprintf(buff, sizeof(buff), "%d", game_manager.map.grid[i][j]);

      Vector2 textSize = MeasureTextEx(GetFontDefault(), buff, 20, 1.0f);
      DrawTextEx(
          GetFontDefault(), buff,
          (Vector2){center.x - textSize.x / 2.0f, center.y - textSize.y / 2.0f},
          20, 1.0f, WHITE);
    }
  }
}

void renderer_hud() {
  DrawTexture(*asset_manager_get_hud_texture(), 0, 0, WHITE);
}
