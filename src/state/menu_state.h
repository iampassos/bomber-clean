#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "state/state.h"
#include <raylib.h>

typedef struct {
  char *text;
  Vector2 position;
  float size;
  float spacing;
  Font font;
  Color color;
} Text;

typedef struct {
  State state;
} MenuState;

void menu_state_init();
void menu_state_update();
void menu_state_render();

#endif
