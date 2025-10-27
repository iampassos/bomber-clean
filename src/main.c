#include "common.h"
#include "map.h"
#include "player.h"
#include <raylib.h>

float delta_time = 0;

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bomber Clean");

  SetTargetFPS(60);

  Map *map = map_init();

  player_new(0, (Vector2){SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f},
             TILE_SIZE - 8, TILE_SIZE + 6);

  while (!WindowShouldClose()) {
    delta_time = GetFrameTime();

    BeginDrawing();

    player_update_all();

    ClearBackground(RAYWHITE);

    for (int i = 0; i < GRID_HEIGHT; i++)
      for (int j = 0; j < GRID_WIDTH; j++)
        DrawRectangle(MAP_X_OFFSET + j * TILE_SIZE,
                      MAP_Y_OFFSET + i * TILE_SIZE, TILE_SIZE, TILE_SIZE,
                      TILE_COLORS[map->grid[i][j]]);

    for (int i = 0; i <= GRID_WIDTH; i++)
      DrawLine(MAP_X_OFFSET + i * TILE_SIZE, MAP_Y_OFFSET,
               MAP_X_OFFSET + i * TILE_SIZE,
               MAP_Y_OFFSET + GRID_HEIGHT * TILE_SIZE,
               (Color){128, 128, 128, 32});

    for (int i = 0; i < GRID_HEIGHT; i++)
      DrawLine(MAP_X_OFFSET, MAP_Y_OFFSET + i * TILE_SIZE,
               MAP_X_OFFSET + TILE_SIZE * GRID_WIDTH,
               MAP_Y_OFFSET + i * TILE_SIZE, (Color){128, 128, 128, 32});

    for (int i = 0; i < player_count; i++) {
      Player *p = players[i];
      DrawRectangle(p->position.x, p->position.y, p->width, p->height, BEIGE);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
