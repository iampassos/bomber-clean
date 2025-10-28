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

  controllers_init(controllers, &controllers_n);

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    delta_time = GetFrameTime();

    BeginDrawing();

    player_update_all();

    ClearBackground(BLACK);

    for (int i = 0; i < GRID_HEIGHT; i++)
      for (int j = 0; j < GRID_WIDTH; j++)
        DrawRectangle(MAP_X_OFFSET + j * TILE_SIZE,
                      MAP_Y_OFFSET + i * TILE_SIZE, TILE_SIZE, TILE_SIZE,
                      TILE_COLORS[state.map.grid[i][j]]);

    for (int i = 0; i < state.player_count; i++) {
      Player *p = &state.players[i];
      DrawTexture(PLAYER_TEXTURES[p->direction][p->animation_step],
                  p->position.x, p->position.y, WHITE);
    }

    player_debug_draw();

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
