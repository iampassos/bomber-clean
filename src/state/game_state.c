#include "game_state.h"
#include "core/assets/asset_manager.h"
#include "entities/entities_manager.h"
#include "game/game_manager.h"
#include "input/input_manager.h"
#include "render/renderer.h"
#include "state_manager.h"
#include <raylib.h>
#include <stdlib.h>

RenderTexture2D target;

void game_state_init() {
  entities_manager_init();
  input_manager_init();
  game_manager_init();

  GameState *game_state = malloc(sizeof(GameState));
  game_state->state.update = game_state_update;
  game_state->state.render = game_state_render;

  state_manager.type = STATE_GAME;
  state_manager.state = (State *)game_state;

  target = LoadRenderTexture(GAMEPLAY_WIDTH, GAMEPLAY_HEIGHT);

  asset_manager_load_game();
}

void game_state_update() {
  if (game_manager.status == GAME_OVER) {
    state_manager_set(STATE_MENU);
    asset_manager_unload_game();
    return;
  }

  input_manager_update();
  game_manager_update(GetFrameTime());
}

void game_state_render() {
  BeginTextureMode(target);
  ClearBackground(WHITE);

  renderer_draw_game();

  EndTextureMode();

  BeginDrawing();
  ClearBackground(BLACK);

  int offsetX = (GetScreenWidth() - GAMEPLAY_WIDTH) / 2;
  int offsetY = (GetScreenHeight() - GAMEPLAY_HEIGHT) / 2;

  if (IsWindowFullscreen() || GetScreenWidth() == 1920)
    DrawTexture(*asset_manager_get_fullscreen_texture(), 0, 0, WHITE);

  DrawTextureRec(target.texture,
                 (Rectangle){0, 0, GAMEPLAY_WIDTH, -GAMEPLAY_HEIGHT},
                 (Vector2){offsetX, offsetY}, WHITE);

  EndDrawing();
}
