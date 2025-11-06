#include "input_manager.h"
#include "controller.h"
#include "game/game_manager.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_joystick.h>
#include <raylib.h>
#include <string.h>

InputManager input_manager = {0};

void input_manager_init() {
  controllers_init(input_manager.controllers, &input_manager.controllers_n);
}

void input_manager_update() {
  if (input_manager.controllers_n > 0) {
    SDL_PumpEvents();
    SDL_JoystickUpdate();
  }

  for (int i = 0; i < game_manager.player_count; i++) {
    PlayerInput *input = &input_manager.player_inputs[i];

    if (input_manager.controllers_n > 0) {
      ControllerInput c_input = controller_input(input_manager.controllers[i]);
      input->move.x = c_input.left ? -1.0f : c_input.right ? 1.0f : 0.0f;
      input->move.y = c_input.up ? -1.0f : c_input.down ? 1.0f : 0.0f;
      input->place_bomb = c_input.a || c_input.b ? true : false;
    } else {
      input->move.x = IsKeyDown(KEY_A) ? -1.0 : IsKeyDown(KEY_D) ? 1.0f : 0.0f;
      input->move.y = IsKeyDown(KEY_W) ? -1.0 : IsKeyDown(KEY_S) ? 1.0f : 0.0f;
      input->place_bomb = IsKeyDown(KEY_SPACE);
    }
  }

  input_manager.debug = IsKeyDown(KEY_F1);
  input_manager.hitboxes = IsKeyDown(KEY_F2);
  input_manager.grid = IsKeyDown(KEY_F3);
  input_manager.fullscreen = IsKeyDown(KEY_F11);
}

void input_manager_reset() {
  memset(input_manager.player_inputs, 0, sizeof(input_manager.player_inputs));
}

PlayerInput input_manager_get_player_input(int player_id) {
  return input_manager.player_inputs[player_id];
}
