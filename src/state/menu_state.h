#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "state/state.h"
#include <raylib.h>

typedef enum { TEXT_PLAY, TEXT_TUTORIAL, TEXT_LEADERBOARD, TEXT_EXIT } TextType;

typedef struct {
  Vector2 position;
  float size;
  float spacing;
  Color color;
  Font *font;
  char *text;
  void (*action)();
} Text;

typedef struct {
  State state;
  Texture2D *background;
  int buttons_n;
  Text *buttons;
  TextType selected;
} MenuState;

void menu_state_init();
void menu_state_update();
void menu_state_render();

void menu_state_play_action();
void menu_state_tutorial_action();
void menu_state_leaderboard_action();
void menu_state_exit_action();

#endif
