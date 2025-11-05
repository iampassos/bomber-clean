#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SDL2/SDL_joystick.h>
#include <raylib.h>

typedef struct ControllerInput {
  bool a;
  bool b;
  bool y;
  bool x;
  bool select;
  bool start;
  bool up;
  bool down;
  bool right;
  bool left;
  bool lt;
  bool rt;
} ControllerInput;

void controllers_init(SDL_Joystick *controllers[], int *controllers_n);

ControllerInput controller_input(SDL_Joystick *joy);
ControllerInput controllers_all_inputs(SDL_Joystick *controllers[],
                                       int controller_n);

#endif
