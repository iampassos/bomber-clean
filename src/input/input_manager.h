#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "core/common.h"
#include <raylib.h>

typedef struct {
  Vector2 move;
  bool place_bomb;
} PlayerInput;

typedef enum { ORIGIN_KEYBOARD, ORIGIN_CONTROLLER } InputOrigin;

typedef struct {
  PlayerInput player_inputs[MAX_PLAYERS];
  InputOrigin input_origins[MAX_PLAYERS];
  float last_bomb_input[MAX_PLAYERS];
} InputManager;

extern InputManager input_manager;

void input_manager_init();
void input_manager_update();
void input_manager_reset();

PlayerInput input_manager_get_player_input(int player_id);

#endif
