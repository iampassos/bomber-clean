#include "entity.h"

Vector2 entity_grid_to_world(Entity *entity, GridPosition grid) {
  Vector2 center = map_grid_to_world_center(grid);
  return (Vector2){center.x - entity->width / 2.0f,
                   center.y - entity->height / 2.0f - entity->height_tolerance};
}

GridPosition entity_world_to_grid(Entity *entity) {
  Vector2 feet_position =
      (Vector2){entity->position.x + entity->width / 2.0f,
                entity->position.y +
                    (entity->direction == DIR_UP
                         ? entity->height * 1.1f
                         : entity->height * 0.60f + entity->height_tolerance)};
  GridPosition pos = map_world_to_grid(feet_position);
  return pos;
}
