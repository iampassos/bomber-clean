#include "common.h"
#include "core/map.h"
#include "game/game_manager.h"
#include <math.h>

bool physics_can_move_to(Vector2 projected, float width, float height) {
  int left = (projected.x - MAP_X_OFFSET) / TILE_SIZE;
  int right = (projected.x + width - 1 - MAP_X_OFFSET) / TILE_SIZE;
  int top = (projected.y - MAP_Y_OFFSET) / TILE_SIZE;
  int bottom = (projected.y + height - 1 - MAP_Y_OFFSET) / TILE_SIZE;

  left = fmax(0, fmin(left, GRID_WIDTH - 1));
  right = fmax(0, fmin(right, GRID_WIDTH - 1));
  top = fmax(0, fmin(top, GRID_HEIGHT - 1));
  bottom = fmax(0, fmin(bottom, GRID_HEIGHT - 1));

  for (int row = top; row <= bottom; row++)
    for (int col = left; col <= right; col++)
      if (!map_is_walkable(game_manager.map, (GridPosition){col, row}))
        return false;

  return true;
}
