#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "core/common.h"
#include <SDL2/SDL_joystick.h>
#include <raylib.h>

typedef struct {
  Vector2 move;
  bool place_bomb;
} PlayerInput;

typedef enum { ORIGIN_KEYBOARD, ORIGIN_CONTROLLER } InputOrigin;

typedef struct {
  PlayerInput player_inputs[MAX_PLAYERS];

  InputOrigin input_origins[MAX_PLAYERS];
  float last_input[MAX_PLAYERS];

  SDL_Joystick *controllers[4];
  int controllers_n;

  float last_dev_input;
  bool debug;
  bool hitboxes;
  bool grid;
  bool fullscreen;
  bool fps;
} InputManager;

extern InputManager input_manager;

void input_manager_init();
void input_manager_update();
void input_manager_reset();

PlayerInput input_manager_get_player_input(int player_id);

#endif
