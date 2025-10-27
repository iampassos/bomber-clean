#include <raylib.h>
#include <stdlib.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define TILE_SIZE 48
#define GRID_WIDTH 13
#define GRID_HEIGHT 15

#define MAP_X_OFFSET (SCREEN_WIDTH / 2 - TILE_SIZE * GRID_WIDTH / 2)
#define MAP_Y_OFFSET 0

typedef enum {
    TILE_EMPTY,
    TILE_WALL,
    TILE_BRICK,
} TileType;

typedef struct Map {
    TileType grid[GRID_WIDTH][GRID_HEIGHT];
} Map;

Map *init_map() {
    Map *map = malloc(sizeof(Map));

    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
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

        for (int i = 0; i <= GRID_WIDTH; i++)
            DrawLine(MAP_X_OFFSET + i * TILE_SIZE, MAP_Y_OFFSET, MAP_X_OFFSET + i * TILE_SIZE,
                     MAP_Y_OFFSET + GRID_HEIGHT * TILE_SIZE, GRAY);

        for (int i = 0; i < GRID_HEIGHT; i++)
            DrawLine(MAP_X_OFFSET, MAP_Y_OFFSET + i * TILE_SIZE,
                     MAP_X_OFFSET + TILE_SIZE * GRID_WIDTH, MAP_Y_OFFSET + i * TILE_SIZE, GRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
