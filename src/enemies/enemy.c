#include "enemy.h"
#include "entities/entities_manager.h"
#include <stdlib.h>

Enemy *enemy_at_grid(GridPosition grid) {
  for (int i = 0; i < entities_manager.count; i++) {
    Entity *entity = entities_manager.entries[i];

    if (entity->type == ENTITY_ENEMY) {
      GridPosition grid2 =
          entity_world_to_grid(entity, entity->height_tolerance);
      if (map_is_same_grid(grid, grid2))
        return (Enemy *)entity;
    }
  }

  return NULL;
}
