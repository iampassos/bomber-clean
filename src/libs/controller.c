#include "controller.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

void controllers_init(SDL_Joystick *controllers[], int *controllers_n) {
  if (SDL_Init(SDL_INIT_JOYSTICK) < 0) {
    printf("SDL_Init Error: %s\n", SDL_GetError());
    return;
  }

  for (int i = 0; i < SDL_NumJoysticks(); i++) {
    SDL_Joystick *joy = SDL_JoystickOpen(i);
    if (joy) {
      printf("Joystick %d: %s\n", i, SDL_JoystickName(joy));
      controllers[*controllers_n] = joy;
      (*controllers_n)++;
    }

    if (*controllers_n >= 4)
      break;
  }
}

ControllerInput controller_input(SDL_Joystick *joy) {
  ControllerInput input = {0};

  if (!joy)
    return input;

  short x = SDL_JoystickGetAxis(joy, 0);
  short y = SDL_JoystickGetAxis(joy, 1);

  input.left = (x < -10000);
  input.right = (x > 10000);
  input.up = (y < -10000);
  input.down = (y > 10000);

  input.a = SDL_JoystickGetButton(joy, 1);
  input.b = SDL_JoystickGetButton(joy, 2);
  input.x = SDL_JoystickGetButton(joy, 0);
  input.y = SDL_JoystickGetButton(joy, 3);

  input.start = SDL_JoystickGetButton(joy, 9);
  input.select = SDL_JoystickGetButton(joy, 8);

  input.lt = SDL_JoystickGetButton(joy, 4);
  input.rt = SDL_JoystickGetButton(joy, 5);

  return input;
}

ControllerInput controllers_all_inputs(SDL_Joystick *controllers[],
                                       int controller_n) {
  ControllerInput temp = {0};

  for (int i = 0; i < controller_n; i++) {
    ControllerInput input = controller_input(controllers[i]);

    temp.up |= input.up;
    temp.down |= input.down;
    temp.left |= input.left;
    temp.right |= input.right;

    temp.a |= input.a;
    temp.b |= input.b;
    temp.x |= input.x;
    temp.y |= input.y;

    temp.lt |= input.lt;
    temp.rt |= input.rt;
    temp.start |= input.start;
    temp.select |= input.select;
  }

  return temp;
}
