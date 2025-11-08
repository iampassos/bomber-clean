#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "state/state.h"

typedef enum { STATE_MENU, STATE_GAME } StateType;

typedef struct {
  StateType type;
  State state;
} StateManager;

extern StateManager state_manager;

void state_manager_init();
void state_manager_update();
void state_manager_render();

void state_manager_set(StateType type);

#endif
