#include <raylib.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

float delta_time = 0;

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bomber Clean");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
