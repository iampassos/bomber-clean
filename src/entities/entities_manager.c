#include "entities_manager.h"
#include "core/common.h"
#include "core/map.h"
#include "entities/entity.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
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
  for (int i = 0; i < entities_manager.count; i++)
    free(entities_manager.entries[i]);

  entities_manager.count = 0;
};

void entities_manager_clear_but_player() {
  for (int i = 0; i < entities_manager.count; i++) {
    Entity *entity = entities_manager.entries[i];
    if (entity->type != ENTITY_PLAYER)
      entities_manager_remove(entity);
  }
}

float old_x_offset = 0;
float old_y_offset = 0;

void entities_manager_recalculate_positions() {
  for (int i = 0; i < entities_manager.count; i++) {
    Entity *entity = entities_manager.entries[i];

    entity->position.x -= old_x_offset;
    entity->position.y -= old_y_offset;

    entity->position.x += MAP_X_OFFSET;
    entity->position.y += MAP_Y_OFFSET;
  }

  old_x_offset = MAP_X_OFFSET;
  old_y_offset = MAP_Y_OFFSET;
}

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
  float y = (GAMEPLAY_HEIGHT + MAP_Y_OFFSET) / 4.0f - textSize.y / 2.0f;

  DrawRectangle(x, y, textSize.x + 10, textSize.y + 10,
                (Color){196, 196, 196, 200});

  DrawTextEx(GetFontDefault(), strBuffer, (Vector2){x, y}, 20, 1.0f, BLACK);
}
