#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "state/state.h"
#include <raylib.h>

typedef enum { TEXT_NONE, TEXT_PLAY } TextType;

typedef struct {
  Vector2 position;
  float size;
  float spacing;
  Color color;
  Font *font;
  char *text;
} Text;

typedef struct {
  State state;
  TextType current;
  Texture2D *background;
} MenuState;

void menu_state_init();
void menu_state_update();
void menu_state_render();

#endif
