#include "core/assets/asset_manager.h"
#include "core/common.h"
#include <raylib.h>

#include "rng.h"
#include "state/state_manager.h"

int main(void) {
  seed_rng();

  SetConfigFlags(FLAG_VSYNC_HINT);

  InitWindow(GAMEPLAY_WIDTH, GAMEPLAY_HEIGHT, "Bomber Clean");

  InitAudioDevice();

  state_manager_init();

  while (!WindowShouldClose()) {
    state_manager_update();
    state_manager_render();
  }

  CloseAudioDevice();
  CloseWindow();

  return 0;
}
