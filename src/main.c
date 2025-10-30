#include "core/asset_manager.h"
#include "core/common.h"
#include "core/map.h"
#include "entities/entities_manager.h"
#include "entities/player.h"
#include "game/game_manager.h"
#include "render/input_manager.h"
#include "render/renderer.h"
#include <raylib.h>

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BomberClean");

  entities_manager_init();
  input_manager_init();
  game_manager_init();

  map_init(&game_manager.map, MAP_STAGE_1);

  asset_manager_init();
  asset_manager_load_all();
  asset_manager_load_map_textures(game_manager.map.stage);

  player_create(0, (Vector2){0, 0});

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    input_manager_update();
    game_manager_update();

    BeginDrawing();

    ClearBackground(BLACK);

    renderer_draw_game();

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
