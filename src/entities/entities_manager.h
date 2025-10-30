#ifndef ENTITIES_MANAGER_H
#define ENTITIES_MANAGER_H

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
void entities_manager_clear();

#endif
