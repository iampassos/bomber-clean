#include "core/asset_manager.h"
#include "core/common.h"
#include "entities/entities_manager.h"
#include "game/game_manager.h"
#include "input/input_manager.h"
#include "render/renderer.h"
#include <raylib.h>
#include <stdlib.h>
#include <time.h>

// Aleatoriedade para windows ou mac/linux

#if defined(_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <process.h>
#include <windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif
#include <stdlib.h>

void seed_rng() {
#if defined(_WIN32) || defined(_WIN64)
  LARGE_INTEGER li;
  QueryPerformanceCounter(&li);
  srand((unsigned int)(li.QuadPart ^ _getpid()));
#else
  struct timeval tv;
  gettimeofday(&tv, NULL);
  srand(tv.tv_usec ^ tv.tv_sec ^ getpid());
#endif
}

int main(void) {
  seed_rng();

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bomber Clean");

  entities_manager_init();
  input_manager_init();
  game_manager_init();
  asset_manager_init();

  asset_manager_load_all();

  game_manager_start_stage();

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();

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
