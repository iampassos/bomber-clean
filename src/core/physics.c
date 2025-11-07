#include "physics.h"
#include "common.h"
#include "core/map.h"
#include "entities/bomb.h"
#include "entities/entities_manager.h"
#include "entities/entity.h"
#include "entities/player.h"
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

bool physics_can_move_to_entities(Entity *self, Vector2 projected,
                                  bool bomb_passthrough) {
  int left = (projected.x - MAP_X_OFFSET) / TILE_SIZE;
  int right = (projected.x + self->width - 1 - MAP_X_OFFSET) / TILE_SIZE;
  int top = (projected.y - MAP_Y_OFFSET) / TILE_SIZE;
  int bottom = (projected.y + self->height - 1 - MAP_Y_OFFSET) / TILE_SIZE;

  left = fmax(0, fmin(left, GRID_WIDTH - 1));
  right = fmax(0, fmin(right, GRID_WIDTH - 1));
  top = fmax(0, fmin(top, GRID_HEIGHT - 1));
  bottom = fmax(0, fmin(bottom, GRID_HEIGHT - 1));

  Rectangle this = {projected.x, projected.y, self->width - 1,
                    self->height - 1};

  for (int row = top; row <= bottom; row++) {
    for (int col = left; col <= right; col++) {
      GridPosition grid = {col, row};

      if (!map_is_walkable(game_manager.map, grid))
        return false;

      for (int i = 0; i < entities_manager.count; i++) {
        Entity *entity = entities_manager.entries[i];

        if (entity == self)
          continue;

        if (entity->type == ENTITY_BOMB && bomb_passthrough)
          if (((Bomb *)entity)->player_id == ((Player *)self)->id)
            continue;

        if (entity->type == ENTITY_PLAYER || entity->type == ENTITY_ENEMY ||
            entity->type == ENTITY_BOMB) {
          Rectangle other = {entity->position.x,
                             entity->position.y + entity->height_tolerance,
                             entity->width - 1, entity->height - 1};

          if (CheckCollisionRecs(this, other))
            return false;
        };
      }
    }
  }

  return true;
}

bool physics_entity_collision(Entity *a, Entity *b) {
  return CheckCollisionRecs(
      (Rectangle){a->position.x, a->position.y + a->height_tolerance, a->width,
                  a->height},
      (Rectangle){b->position.x, b->position.y + b->height_tolerance, b->width,
                  b->height});
}
