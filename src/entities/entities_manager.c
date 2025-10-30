#include "entities_manager.h"
#include "core/map.h"
#include "entities/bomb.h"
#include "entities/entity.h"
#include <string.h>

EntitiesManager entities_manager = {0};

void entities_manager_init() {}

void entities_manager_add(Entity *entity) {
  if (entities_manager.count >= MAX_ENTITIES)
    return;

  entities_manager.entries[entities_manager.count++] = entity;
}

void entities_manager_remove(Entity *entity) {
  if (entities_manager.count >= MAX_ENTITIES)
    return;

  int idx = -1;
  for (int i = 0; i < entities_manager.count; i++)
    if (entities_manager.entries[i] == entity)
      idx = i;

  if (idx == -1)
    return;

  for (int i = idx; i < entities_manager.count - 1; i++)
    entities_manager.entries[i] = entities_manager.entries[i + 1];
}

void entities_manager_update_all() {
  for (int i = 0; i < entities_manager.count; i++) {
    Entity *entity = entities_manager.entries[i];

    if (entity->update != NULL)
      entity->update(entity);
  }
}

void entities_manager_draw_all() {
  for (int i = 0; i < entities_manager.count; i++) {
    Entity *entity = entities_manager.entries[i];

    if (entity->draw != NULL)
      entity->draw(entity);
  }
}

void entities_manager_debug_all() {
  for (int i = 0; i < entities_manager.count; i++) {
    Entity *entity = entities_manager.entries[i];

    if (entity->debug != NULL)
      entity->debug(entity);
  }
}

void entities_manager_clear() {
  memset(entities_manager.entries, 0, sizeof(entities_manager.entries));
};

int entities_manager_get_all_at_grid(GridPosition grid, EntityType type,
                                     Entity **out, int max_out) {
  int count = 0;
  for (int i = 0; i < MAX_ENTITIES && count < max_out; i++) {
    Entity *entity = entities_manager.entries[i];

    if (entity == NULL)
      break;

    GridPosition pos = map_world_to_grid(entity->position);

    if (entity->type == type && pos.col == grid.col && pos.row == grid.row)
      out[count++] = entity;
  }

  return count;
}

int entities_manager_get_all_from_type(EntityType type, Entity **out,
                                       int max_out) {
  int count = 0;
  for (int i = 0; i < MAX_ENTITIES && count < max_out; i++) {
    Entity *entity = entities_manager.entries[i];

    if (entity == NULL)
      break;

    if (entity->type == type)
      out[count++] = entity;
  }

  return count;
}

int entities_manager_get_all_player_bombs(Player *player, Entity **out) {
  int count = 0;
  for (int i = 0; i < MAX_ENTITIES && count <= player->bomb_capacity; i++) {
    Entity *entity = entities_manager.entries[i];

    if (entity == NULL)
      break;

    Bomb *bomb = (Bomb *)entity;

    if (entity->type == ENTITY_BOMB && bomb->player_id == player->id)
      out[count++] = entity;
  }

  return count;
}
