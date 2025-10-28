#include "common.h"
#include "controller.h"
#include "map.h"
#include "player.h"
#include "state.h"
#include <raylib.h>

float delta_time = 0;

SDL_GameController *controllers[MAX_PLAYERS];
int controllers_n = 0;

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bomber Clean");

  state_init();
  player_init();

  map_load_first();

  controllers_init(controllers, &controllers_n);

  SetTargetFPS(60);

  float last = GetTime();

  while (!WindowShouldClose()) {
    delta_time = GetFrameTime();

    BeginDrawing();

    player_update_all();

    if (IsKeyDown(KEY_F1) && GetTime() - last > 0.25f) {
      state.view_mode = state.view_mode == DEBUG ? NORMAL : DEBUG;
      last = GetTime();
    }

    ClearBackground(BLACK);

    state.map.draw();

    for (int i = 0; i < state.player_count; i++) {
      Player *p = &state.players[i];
      DrawTexture(PLAYER_TEXTURES[p->direction][p->animation_step],
                  p->position.x, p->position.y, WHITE);
    }

    if (state.view_mode == DEBUG) {
      for (int i = 0; i <= GRID_WIDTH; i++)
        DrawLine(MAP_X_OFFSET + i * TILE_SIZE, MAP_Y_OFFSET,
                 MAP_X_OFFSET + i * TILE_SIZE,
                 MAP_Y_OFFSET + GRID_HEIGHT * TILE_SIZE,
                 (Color){128, 128, 128, 128});

      for (int i = 0; i < GRID_HEIGHT; i++)
        DrawLine(MAP_X_OFFSET, MAP_Y_OFFSET + i * TILE_SIZE,
                 MAP_X_OFFSET + TILE_SIZE * GRID_WIDTH,
                 MAP_Y_OFFSET + i * TILE_SIZE, (Color){128, 128, 128, 128});

      player_debug_draw();
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
