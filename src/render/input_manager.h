#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "core/common.h"
#include <raylib.h>

typedef struct {
  Vector2 move;
  bool place_bomb;
} PlayerInput;

typedef struct {
  PlayerInput player_inputs[MAX_PLAYERS];
} InputManager;

extern InputManager input_manager;

void input_manager_init();
void input_manager_update();
void input_manager_reset();

#endif
