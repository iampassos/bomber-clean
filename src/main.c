#include <raylib.h>
#include <stdlib.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

#define TILE_SIZE 48
#define GRID_WIDTH 15
#define GRID_HEIGHT 13
#define GRID_SIZE (GRID_WIDTH * GRID_HEIGHT)

#define MAP_X_OFFSET (SCREEN_WIDTH / 2 - TILE_SIZE * GRID_WIDTH / 2)
#define MAP_Y_OFFSET (SCREEN_HEIGHT / 2 - TILE_SIZE * GRID_HEIGHT / 2)

typedef enum {
  TILE_EMPTY,
  TILE_WALL,
  TILE_BRICK,
} TileType;

const Color TILE_COLORS[3] = {
    [TILE_EMPTY] = (Color){17, 92, 51, 255},
    [TILE_WALL] = (Color){101, 101, 101, 255},
    [TILE_BRICK] = (Color){58, 58, 58, 255},
};

typedef struct Map {
  TileType grid[GRID_HEIGHT][GRID_WIDTH];
} Map;

Map *init_map() {
  Map *map = malloc(sizeof(Map));

  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      if (i == 0 || j == 0 || i + 1 == GRID_HEIGHT || j + 1 == GRID_WIDTH ||
          (i % 2 == 0 && j % 2 == 0))
        map->grid[i][j] = TILE_WALL;
      else
        map->grid[i][j] = TILE_EMPTY;
    }
  }

  return map;
}

float delta_time = 0;

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bomber Clean");

  SetTargetFPS(60);

  Map *map = init_map();

  while (!WindowShouldClose()) {
    delta_time = GetFrameTime();

    BeginDrawing();

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

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
