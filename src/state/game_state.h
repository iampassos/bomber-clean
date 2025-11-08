#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "state/state.h"

typedef struct {
  State state;
} GameState;

void game_state_init();
void game_state_update();
void game_state_render();

#endif
