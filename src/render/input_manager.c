#include "input_manager.h"
#include <raylib.h>
#include <stdio.h>
#include <string.h>

InputManager input_manager = {0};

void input_manager_init() {}

void input_manager_update() {
  PlayerInput *input = &input_manager.player_inputs[0];

  input->move.x = IsKeyDown(KEY_A) ? -1.0 : IsKeyDown(KEY_D) ? 1.0f : 0.0f;
  input->move.y = IsKeyDown(KEY_W) ? -1.0 : IsKeyDown(KEY_S) ? 1.0f : 0.0f;
  input->place_bomb = IsKeyDown(KEY_SPACE);
}

void input_manager_reset() {
  memset(input_manager.player_inputs, 0, sizeof(input_manager.player_inputs));
}
