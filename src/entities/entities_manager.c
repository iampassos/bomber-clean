#include "entities_manager.h"
#include "core/map.h"
#include "entities/entity.h"
#include <stdio.h>
#include <string.h>

EntitiesManager entities_manager = {0};

void entities_manager_init() {}

void entities_manager_add(Entity *entity) {
  if (entities_manager.count >= MAX_ENTITIES)
    return;

  entities_manager.entries[entities_manager.count++] = entity;
}

void entities_manager_remove(Entity *entity) {
  if (!entity || entities_manager.count <= 0)
    return;

  int idx = -1;
  for (int i = 0; i < entities_manager.count; i++) {
    if (entities_manager.entries[i] == entity) {
      idx = i;
      break;
    }
  }

  if (idx == -1)
    return;

  for (int i = idx; i < entities_manager.count - 1; i++)
    entities_manager.entries[i] = entities_manager.entries[i + 1];

  entities_manager.count--;

  if (entities_manager.count >= 0)
    entities_manager.entries[entities_manager.count] = NULL;
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

void entities_manager_draw_all_layer(EntityLayer layer) {
  for (int i = 0; i < entities_manager.count; i++) {
    Entity *entity = entities_manager.entries[i];

    if (entity->layer == layer && entity->draw != NULL)
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

int entities_manager_get_all_at_grid(GridPosition grid, Entity **out,
                                     int max_out) {
  int count = 0;
  for (int i = 0; i < MAX_ENTITIES && count < max_out; i++) {
    Entity *entity = entities_manager.entries[i];

    if (entity == NULL)
      break;

    GridPosition pos = map_world_to_grid(entity->position);

    if (pos.col == grid.col && pos.row == grid.row) {
      if (out != NULL)
        out[count] = entity;
      count++;
    }
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

    if (entity->type == type) {
      if (out != NULL)
        out[count] = entity;
      count++;
    }
  }

  return count;
}

void entities_manager_debug() {
  char strBuffer[1000];
  snprintf(strBuffer, sizeof(strBuffer),
           "Entities Manager debug\n"
           "entities: %d",
           entities_manager.count);

  Vector2 textSize = MeasureTextEx(GetFontDefault(), strBuffer, 20, 1.0f);

  float x = 15;
  float y = SCREEN_HEIGHT / 4.0f - textSize.y / 2.0f;

  DrawRectangle(x, y, textSize.x + 10, textSize.y + 10,
                (Color){196, 196, 196, 200});

  DrawTextEx(GetFontDefault(), strBuffer, (Vector2){x, y}, 20, 1.0f, BLACK);
}
