#include "bomb.h"
#include "common.h"
#include "controller.h"
#include "map.h"
#include "player.h"
#include "state.h"
#include <raylib.h>
#include <stdio.h>

float delta_time = 0;

SDL_GameController *controllers[MAX_PLAYERS];
int controllers_n = 0;

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bomber Clean");

  Texture2D top_hud = LoadTexture("assets/hud/TOP_HUD.png");

  state_init();
  controllers_init(controllers, &controllers_n);

  SetTargetFPS(60);

  float last = GetTime();

  while (!WindowShouldClose()) {
    delta_time = GetFrameTime();

    BeginDrawing();

    player_update_all();
    bombs_update_all();
    state.map.update();

    if (IsKeyDown(KEY_F1) && GetTime() - last > 0.25f) {
      state.view_mode = state.view_mode == DEBUG ? NORMAL : DEBUG;
      last = GetTime();
    }

    ClearBackground(BLACK);

    state.map.draw();

    for (int i = 0; i < state.players.count; i++) {
      Player *p = &state.players.entries[i];
      DrawTexture(PLAYER_TEXTURES[p->direction][p->animation_step],
                  p->position.x, p->position.y, WHITE);
    }

    DrawTexture(top_hud, 0, 0, WHITE);

    if (state.view_mode == DEBUG) {
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
          Vector2 center =
              map_get_vector_from_grid_center((GridPosition){j, i});
          char buff[3];
          snprintf(buff, sizeof(buff), "%d", state.map.grid[i][j]);

          Vector2 textSize = MeasureTextEx(GetFontDefault(), buff, 20, 1.0f);
          DrawTextEx(GetFontDefault(), buff,
                     (Vector2){center.x - textSize.x / 2.0f,
                               center.y - textSize.y / 2.0f},
                     20, 1.0f, WHITE);
        }
      }

      for (int i = 0; i < state.players.count; i++)
        player_debug_draw(&state.players.entries[i]);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
