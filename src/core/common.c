#include "common.h"
#include <raylib.h>

float MAP_X_OFFSET;
float MAP_Y_OFFSET;

float last_width;
float last_height;

void common_update_offset() {
  int screenWidth = GetScreenWidth();
  int screenHeight = GetScreenHeight();

  float baseMapX = GAMEPLAY_WIDTH / 2.0f - TILE_SIZE * GRID_WIDTH / 2.0f;
  float baseMapY = GAMEPLAY_HEIGHT - GRID_HEIGHT * TILE_SIZE + TILE_SIZE / 2.0f;

  if (screenWidth == GAMEPLAY_WIDTH && screenHeight == GAMEPLAY_HEIGHT) {
    MAP_X_OFFSET = baseMapX;
    MAP_Y_OFFSET = baseMapY;
  } else {
    float offsetX = (screenWidth - GAMEPLAY_WIDTH) / 2.0f;
    float offsetY = (screenHeight - GAMEPLAY_HEIGHT) / 2.0f;

    MAP_X_OFFSET = baseMapX + offsetX;
    MAP_Y_OFFSET = baseMapY + offsetY;
  }

  last_width = screenWidth;
  last_height = screenHeight;
}

bool common_should_update_offset() {
  return GetScreenWidth() != last_width || GetScreenHeight() != last_height;
}
