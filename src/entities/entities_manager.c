#include "entities_manager.h"
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

void entities_manager_clear() {
  memset(entities_manager.entries, 0, sizeof(entities_manager.entries));
};
