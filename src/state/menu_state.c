#include "menu_state.h"
#include "controller.h"
#include "core/assets/asset_manager.h"
#include "core/assets/assets_sounds.h"
#include "core/score.h"
#include "input/input_manager.h"
#include "state_manager.h"
#include <raylib.h>
#include <stdlib.h>

bool menu_state_is_selecting_text(Text *text, int i) {
  if (input_manager.controllers_n > 0) {
    MenuState *menu_state = (MenuState *)state_manager.state;

    return menu_state->selected == i;
  } else {
    Vector2 mouse = GetMousePosition();

    Vector2 t =
        MeasureTextEx(*text->font, text->text, text->size, text->spacing);

    Rectangle rect = {text->position.x, text->position.y, t.x, t.y};

    return CheckCollisionPointRec(mouse, rect);
  }
}

bool menu_state_is_clicking_text(Text *text, int i) {
  if (input_manager.controllers_n > 0) {
    return menu_state_is_selecting_text(text, i) &&
           (input_manager.controller_input_all.a ||
            input_manager.controller_input_all.b ||
            input_manager.controller_input_all.x ||
            input_manager.controller_input_all.y);
  } else {
    return menu_state_is_selecting_text(text, i) &&
           IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
  }
}

void menu_state_draw_text(Text *text, bool selected) {
  DrawTextEx(*text->font, text->text, text->position, text->size, text->spacing,
             selected ? GOLD : text->color);
}

void menu_state_init() {
  MenuState *menu_state = malloc(sizeof(MenuState));
  menu_state->state.update = menu_state_update;
  menu_state->state.render = menu_state_render;
  menu_state->screen = MENU_INITIAL;
  menu_state->buttons_n = 4;
  menu_state->selected = input_manager.controllers_n > 0 ? TEXT_PLAY : -1;
  menu_state->buttons = malloc(sizeof(Text) * menu_state->buttons_n);
  menu_state->buttons[0] = (Text){{0, 0},
                                  38,
                                  1.0f,
                                  WHITE,
                                  asset_manager_get_font(0),
                                  "PLAY GAME",
                                  menu_state_play_action};

  menu_state->buttons[1] = (Text){{0, 0},
                                  38,
                                  1.0f,
                                  GRAY,
                                  asset_manager_get_font(0),
                                  "TUTORIAL",
                                  menu_state_tutorial_action};

  menu_state->buttons[2] = (Text){{0, 0},
                                  38,
                                  1.0f,
                                  WHITE,
                                  asset_manager_get_font(0),
                                  "LEADERBOARD",
                                  menu_state_leaderboard_action};

  menu_state->buttons[3] = (Text){{0, 0},
                                  38,
                                  1.0f,
                                  WHITE,
                                  asset_manager_get_font(0),
                                  "EXIT",
                                  menu_state_exit_action};

  menu_state->background = asset_manager_get_menu_background_small();

  state_manager.type = STATE_MENU;
  state_manager.state = (State *)menu_state;

  asset_manager_load_menu();

  PlaySound(*assets_sounds_get_menu_music());
}

void menu_state_play_action() {
  state_manager_set(STATE_GAME);

  Sound select = *assets_sounds_get_menu_select();
  if (!IsSoundPlaying(select))
    PlaySound(select);

  StopSound(*assets_sounds_get_menu_music());
  asset_manager_unload_menu();
}

void menu_state_tutorial_action() {}

void menu_state_leaderboard_action() {
  MenuState *menu_state = (MenuState *)state_manager.state;
  menu_state->screen = MENU_LEADERBOARD;
}

void menu_state_exit_action() { state_manager.should_exit = true; }

void menu_state_update_initial() {
  static float last = 0;

  MenuState *menu_state = (MenuState *)state_manager.state;

  if (IsWindowFullscreen() || GetScreenWidth() == 1920) {
    menu_state->background = asset_manager_get_menu_background();
    menu_state->buttons[0].position = (Vector2){791, 657};
    menu_state->buttons[1].position = (Vector2){812, 711};
    menu_state->buttons[2].position = (Vector2){755, 765};
    menu_state->buttons[3].position = (Vector2){886, 819};
  } else {
    menu_state->background = asset_manager_get_menu_background_small();
    menu_state->buttons[0].position = (Vector2){64, 625};
    menu_state->buttons[1].position = (Vector2){64, 679};
    menu_state->buttons[2].position = (Vector2){64, 733};
    menu_state->buttons[3].position = (Vector2){64, 787};
  }

  if (input_manager.controllers_n > 0) {
    ControllerInput c_all = input_manager.controller_input_all;

    if (GetTime() - last >= 0.125f) {
      menu_state->selected = (menu_state->selected + (c_all.down ? 1
                                                      : c_all.up ? -1
                                                                 : 0)) %
                             menu_state->buttons_n;

      last = GetTime();
    }
  }

  bool selected = false;
  static int last_played = -1;

  for (int i = 0; i < menu_state->buttons_n; i++) {
    Text *button = &menu_state->buttons[i];

    if (menu_state_is_selecting_text(button, i)) {
      if (last_played != i) {
        Sound cursor = *assets_sounds_get_menu_cursor();
        StopSound(cursor);
        PlaySound(cursor);
        last_played = i;
      }

      menu_state->selected = i;
      selected = true;
    }

    if (menu_state_is_clicking_text(button, i))
      button->action();
  }

  if (!selected)
    menu_state->selected = -1;
}

void menu_state_update_leaderboard() {
  MenuState *menu_state = (MenuState *)state_manager.state;

  static float last = 0;

  if (IsWindowFullscreen() || GetScreenWidth() == 1920) {
    menu_state->background = asset_manager_get_menu_leaderboard();
  } else {
    menu_state->background = asset_manager_get_menu_leaderboard_small();
  }

  if (IsKeyDown(KEY_ESCAPE))
    menu_state->screen = MENU_INITIAL;

  if (input_manager.controllers_n > 0) {
    ControllerInput c_all = input_manager.controller_input_all;

    if (GetTime() - last >= 0.125f) {
      if (c_all.start || c_all.a)
        menu_state->screen = MENU_INITIAL;
      last = GetTime();
    }
  }
}

void menu_state_update() {
  MenuState *menu_state = (MenuState *)state_manager.state;

  switch (menu_state->screen) {
  case MENU_INITIAL:
    menu_state_update_initial();
    break;
  case MENU_LEADERBOARD:
    menu_state_update_leaderboard();
    break;
  }
}

void menu_state_render() {
  MenuState *menu_state = (MenuState *)state_manager.state;

  BeginDrawing();
  ClearBackground(WHITE);

  DrawTexture(*menu_state->background, 0, 0, WHITE);

  if (menu_state->screen == MENU_INITIAL) {
    for (int i = 0; i < menu_state->buttons_n; i++) {
      Text *button = &menu_state->buttons[i];
      menu_state_draw_text(button, menu_state->selected == i);

      if (menu_state->selected == i)
        DrawTextEx(
            *button->font, ">",
            (Vector2){
                button->position.x - 36,
                button->position.y +
                    MeasureTextEx(*button->font, ">", 24, button->spacing).y /
                        4.0f},
            24, button->spacing, button->color);
    }
  } else {
    Score *ranking = malloc(sizeof(Score) * 5);
    int n = score_get(ranking, 5);

    if (ranking <= 0)
      return;

    for (int i = 0; i < n; i++) {
      if (IsWindowFullscreen() || GetScreenWidth() == 1920)
        DrawTextEx(*menu_state->buttons[0].font,
                   TextFormat("%d. Player %d %.0fs", i + 1, ranking[i].id,
                              ranking[i].time / 1000.0f),
                   (Vector2){608, 359 + (i * 80)}, 42, 0.0f, WHITE);
      else
        DrawTextEx(*menu_state->buttons[0].font,
                   TextFormat("%d. Player %d %.0fs", i + 1, ranking[i].id,
                              ranking[i].time / 1000.0f),
                   (Vector2){164, 229 + (i * 80)}, 42, 0.0f, WHITE);
    }
  }

  EndDrawing();
}
