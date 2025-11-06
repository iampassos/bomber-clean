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
  float off_set_x = MAP_X_OFFSET - TILE_SIZE / 2.0f;
  float off_set_y = MAP_Y_OFFSET - TILE_SIZE * 1.5f;

  DrawTexture(*asset_manager_get_hud_texture(), off_set_x, off_set_y, WHITE);

  for (int i = 0; i < MAX_PLAYERS; i++) {
    Player *player =
        i < game_manager.player_count ? game_manager.players[i] : NULL;

    DrawTextEx(*asset_manager_get_font(0),
               player ? TextFormat("%i", player->lives) : "",
               (Vector2){off_set_x + (i < 2 ? 134 : 730) + (192 * (i % 2)),
                         off_set_y + 45.0f},
               42.0f, 0.0f, WHITE);
  }

  int total_secs = GetTime() - game_manager.game_start;

  int mins = total_secs / 60;
  int secs = total_secs % 60;

  int m1 = mins / 10 % 10;
  int m2 = mins % 10;
  int s1 = secs / 10 % 10;
  int s2 = secs % 10;

  DrawTextEx(*asset_manager_get_font(0), TextFormat("%d", m1),
             (Vector2){off_set_x + 413, off_set_y + 45}, 42, 0, WHITE);
  DrawTextEx(*asset_manager_get_font(0), TextFormat("%d", m2),
             (Vector2){off_set_x + 458, off_set_y + 45}, 42, 0, WHITE);

  DrawTextEx(*asset_manager_get_font(0), ":",
             (Vector2){off_set_x + 496, off_set_y + 46}, 42, 0, WHITE);

  DrawTextEx(*asset_manager_get_font(0), TextFormat("%d", s1),
             (Vector2){off_set_x + 529, off_set_y + 45}, 42, 0, WHITE);
  DrawTextEx(*asset_manager_get_font(0), TextFormat("%d", s2),
             (Vector2){off_set_x + 574, off_set_y + 45}, 42, 0, WHITE);
}
