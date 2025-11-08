#include "menu_state.h"
#include "core/assets/asset_manager.h"
#include "core/assets/assets_sounds.h"
#include "state_manager.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

Text play_text;

bool menu_state_is_touching_text(Text text) {
  Vector2 mouse = GetMousePosition();

  Vector2 t = MeasureTextEx(*text.font, text.text, text.size, text.spacing);

  Rectangle rect = {text.position.x, text.position.y, t.x, t.y};

  return CheckCollisionPointRec(mouse, rect);
}

bool menu_state_is_clicking_text(Text text) {
  return menu_state_is_touching_text(text) &&
         IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void menu_state_draw_text(Text text) {
  DrawTextEx(*text.font, text.text, text.position, text.size, text.spacing,
             text.color);
}

void menu_state_init() {
  MenuState *menu_state = malloc(sizeof(MenuState));
  menu_state->state.update = menu_state_update;
  menu_state->state.render = menu_state_render;

  state_manager.type = STATE_MENU;
  state_manager.state = (State *)menu_state;

  asset_manager_load_menu();

  PlaySound(*assets_sounds_get_menu_music());

  play_text = (Text){
      {0, 0}, 38, 1.0f, WHITE, asset_manager_get_font(0), "PLAY GAME",
  };
}

void menu_state_update() {
  MenuState *menu_state = (MenuState *)state_manager.state;

  if (IsWindowFullscreen() || GetScreenWidth() == 1920) {
    menu_state->background = asset_manager_get_menu_background();
    play_text.position = (Vector2){791, 649};
  } else {
    menu_state->background = asset_manager_get_menu_background_small();
    play_text.position = (Vector2){343, 531};
  }

  if (menu_state_is_touching_text(play_text)) {
    if (menu_state->current != TEXT_PLAY) {
      Sound cursor = *assets_sounds_get_menu_cursor();
      if (!IsSoundPlaying(cursor))
        PlaySound(cursor);
    }

    play_text.color = GOLD;
    menu_state->current = TEXT_PLAY;
  } else {
    menu_state->current = TEXT_NONE;
    play_text.color = WHITE;
  }

  if (menu_state_is_clicking_text(play_text)) {
    state_manager_set(STATE_GAME);

    Sound select = *assets_sounds_get_menu_select();
    if (!IsSoundPlaying(select))
      PlaySound(select);

    StopSound(*assets_sounds_get_menu_music());
    asset_manager_unload_menu();
  }
}

void menu_state_render() {
  MenuState *menu_state = (MenuState *)state_manager.state;

  BeginDrawing();
  ClearBackground(WHITE);

  DrawTexture(*menu_state->background, 0, 0, WHITE);

  menu_state_draw_text(play_text);

  EndDrawing();
}
