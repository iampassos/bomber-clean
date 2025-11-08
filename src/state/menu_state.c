#include "menu_state.h"
#include "core/assets/asset_manager.h"
#include "state_manager.h"
#include <raylib.h>

Rectangle play = {364, 528, 295, 83};

Text play_text;

bool menu_state_is_touching_text(Text text) {
  Vector2 mouse = GetMousePosition();

  Vector2 t = MeasureTextEx(text.font, text.text, text.size, text.spacing);

  Rectangle rect = {text.position.x, text.position.y, t.x, t.y};

  return CheckCollisionPointRec(mouse, rect);
}

bool menu_state_is_clicking_text(Text text) {
  return menu_state_is_touching_text(text) &&
         IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void menu_state_draw_text(Text text) {
  DrawTextEx(text.font, text.text, text.position, text.size, text.spacing,
             text.color);
}

void menu_state_init() {
  state_manager.type = STATE_MENU;
  state_manager.state.update = menu_state_update;
  state_manager.state.render = menu_state_render;

  play_text = (Text){
      "PLAY GAME", {364, 528}, 38, 1.0f, *asset_manager_get_font(0), WHITE};
}

void menu_state_update() {
  play_text.color = menu_state_is_touching_text(play_text) ? GOLD : WHITE;

  if (menu_state_is_clicking_text(play_text))
    state_manager_set(STATE_GAME);
}

void menu_state_render() {
  BeginDrawing();
  ClearBackground(WHITE);

  if (IsWindowFullscreen() || GetScreenWidth() == 1920)
    DrawTexture(*asset_manager_get_menu_background(), 0, 0, WHITE);
  else {
    DrawTexture(*asset_manager_get_menu_background_small(), 0, 0, WHITE);
    menu_state_draw_text(play_text);
  }

  EndDrawing();
}
