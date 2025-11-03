#ifndef ENTITIES_MANAGER_H
#define ENTITIES_MANAGER_H

#include "core/map.h"
#include "entity.h"

#define MAX_ENTITIES 256

typedef struct {
  Entity *entries[MAX_ENTITIES];
  int count;
} EntitiesManager;

extern EntitiesManager entities_manager;

void entities_manager_init();
void entities_manager_add(Entity *entity);
void entities_manager_remove(Entity *entity);
void entities_manager_update_all();
void entities_manager_draw_all();
void entities_manager_draw_all_layer(EntityLayer layer);
void entities_manager_debug_all();
void entities_manager_clear();
void entities_manager_recalculate_positions();

int entities_manager_get_all_at_grid(GridPosition grid, Entity **out,
                                     int max_out);
int entities_manager_get_all_from_type(EntityType type, Entity **out,
                                       int max_out);

void entities_manager_debug();

#endif
