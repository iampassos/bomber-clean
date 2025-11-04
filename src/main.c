#include "core/assets/asset_manager.h"
#include "core/common.h"
#include "entities/entities_manager.h"
#include "game/game_manager.h"
#include "input/input_manager.h"
#include "render/renderer.h"
#include <raylib.h>

#include "rng.h"

int main(void) {
  seed_rng();

  InitWindow(GAMEPLAY_WIDTH, GAMEPLAY_HEIGHT, "Bomber Clean");

  common_update_offset();
  entities_manager_recalculate_positions();

  entities_manager_init();
  input_manager_init();
  game_manager_init();
  asset_manager_init();

  asset_manager_load_all();

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    if (common_should_update_offset()) {
      common_update_offset();
      entities_manager_recalculate_positions();
    }

    input_manager_update();
    game_manager_update(dt);

    BeginDrawing();

    ClearBackground(BLACK);

    renderer_draw_game();

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
