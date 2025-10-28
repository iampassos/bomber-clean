#include "player.h"
#include "common.h"
#include "controller.h"
#include "map.h"
#include <SDL2/SDL_gamecontroller.h>
#include <math.h>
#include <raylib.h>
#include <state.h>

#define SPEED 4.0f
#define ANIMATION_STEP_MS 500

const char *PLAYER_IMAGES_PATH[4][3] = {
    {
        "assets/sprites/player/BomberManUp1.png",
        "assets/sprites/player/BomberManUp2.png",
        "assets/sprites/player/BomberManUp3.png",
    },
    {
        "assets/sprites/player/BomberManBack1.png",
        "assets/sprites/player/BomberManBack2.png",
        "assets/sprites/player/BomberManBack3.png",
    },
    {
        "assets/sprites/player/BomberManLeft1.png",
        "assets/sprites/player/BomberManLeft2.png",
        "assets/sprites/player/BomberManLeft3.png",
    },
    {
        "assets/sprites/player/BomberManRight1.png",
        "assets/sprites/player/BomberManRight2.png",
        "assets/sprites/player/BomberManRight3.png",
    },
};

Image PLAYER_IMAGES[4][3];
Texture2D PLAYER_TEXTURES[4][3];

void player_init() {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 3; j++) {
      PLAYER_IMAGES[i][j] = LoadImage(PLAYER_IMAGES_PATH[i][j]);
      ImageResize(&PLAYER_IMAGES[i][j], TILE_SIZE - 10, TILE_SIZE - 10);
      PLAYER_TEXTURES[i][j] = LoadTextureFromImage(PLAYER_IMAGES[i][j]);
    }
}

void player_new(int id, Vector2 position, float width, float height) {
  Player *player = &state.players[state.player_count++];
  player->id = id;
  player->width = width;
  player->height = height;
  player->direction = DOWN;
  player->state = IDLE;
  player->animation_step = 0;
  player->last_animation_step = 0;

  int col = (position.x - MAP_X_OFFSET) / TILE_SIZE;
  int row = (position.y - MAP_Y_OFFSET) / TILE_SIZE;
  col = fmax(1, fmin(col, GRID_WIDTH - 1));

  for (int r = row; r < GRID_HEIGHT; r++) {
    if (state.map.grid[col][r] == TILE_EMPTY) {
      player->position = (Vector2){MAP_X_OFFSET + col * TILE_SIZE,
                                   MAP_Y_OFFSET + r * TILE_SIZE};
      return;
    }
  }

  player->position = (Vector2){MAP_X_OFFSET + col * TILE_SIZE, MAP_Y_OFFSET};
}

int player_can_move(Vector2 projected, float width, float height) {
  int left = (projected.x - MAP_X_OFFSET) / TILE_SIZE;
  int right = (projected.x + width - MAP_X_OFFSET) / TILE_SIZE;
  int top = (projected.y - MAP_Y_OFFSET) / TILE_SIZE;
  int bottom = (projected.y + height - MAP_Y_OFFSET) / TILE_SIZE;

  left = fmax(0, fmin(left, GRID_WIDTH - 1));
  right = fmax(0, fmin(right, GRID_WIDTH - 1));
  top = fmax(0, fmin(top, GRID_HEIGHT - 1));
  bottom = fmax(0, fmin(bottom, GRID_HEIGHT - 1));

  for (int row = top; row <= bottom; row++) {
    for (int col = left; col <= right; col++) {
      if (state.map.grid[row][col] != TILE_EMPTY)
        return 0;
    }
  }

  return 1;
}

void player_update(Player *player, float x, float y) {
  Vector2 projected = player->position;

  if (x)
    projected.x = fmax(MAP_X_OFFSET, player->position.x + SPEED * x);

  if (y)
    projected.y = fmax(MAP_Y_OFFSET, player->position.y + SPEED * y);

  Vector2 new_pos = player->position;

  Vector2 horizontal = {projected.x, player->position.y};
  if (player_can_move(horizontal, player->width, player->height))
    new_pos.x = horizontal.x;

  Vector2 vertical = {player->position.x, projected.y};
  if (player_can_move(vertical, player->width, player->height))
    new_pos.y = vertical.y;

  float dx = new_pos.x - player->position.x;
  float dy = new_pos.y - player->position.y;

  if (fabs(dx) > fabs(dy)) {
    player->direction = dx > 0 ? RIGHT : LEFT;
    player->state = RUNNING;
  } else if (fabs(dy) > 0.0f) {
    player->direction = dy > 0 ? DOWN : UP;
    player->state = RUNNING;
  } else if (fabs(dy) == 0.0f && fabs(dx) == 0.0f) {
    player->state = IDLE;
    player->animation_step = 0;
  }

  player->position = new_pos;
}

void player_update_all() {
  SDL_GameControllerUpdate();

  SDL_GameController *controller = controllers[0];
  ControllerInput input = controller_input(controller);

  for (int i = 0; i < state.player_count; i++) {
    Player *p = &state.players[i];

    if (p->state == RUNNING && GetTime() - p->last_animation_step >= 0.1f) {
      p->animation_step = (p->animation_step + 1) % 3;
      p->last_animation_step = GetTime();
    }

    if (controller) {
      player_update(p, fabs(input.leftAxis.x) > 0.1f ? input.leftAxis.x : 0.0f,
                    fabs(input.leftAxis.y) > 0.1f ? input.leftAxis.y : 0.0f);

    } else {
      player_update(p,
                    IsKeyDown(KEY_A)   ? -1.0
                    : IsKeyDown(KEY_D) ? 1.0f
                                       : 0.0f,
                    IsKeyDown(KEY_W)   ? -1.0
                    : IsKeyDown(KEY_S) ? 1.0f
                                       : 0.0f);
    }
  }
}

void player_debug_draw() {
  Player *p = &state.players[0];
  char strBuffer[1000];
  snprintf(strBuffer, sizeof(strBuffer),
           "Player debug\n"
           "id: %d\n"
           "position: (%.2f, %.2f)\n"
           "width: %.2f\n"
           "height: %.2f\n"
           "direction: %s\n"
           "state: %s\n"
           "animation-step: %d\n",
           p->id, p->position.x, p->position.y, p->width, p->height,
           p->direction == UP     ? "UP"
           : p->direction == DOWN ? "DOWN"
           : p->direction == LEFT ? "LEFT"
                                  : "RIGHT",
           p->state == IDLE      ? "IDLE"
           : p->state == RUNNING ? "RUNNING"
                                 : "DEAD",
           p->animation_step);

  DrawText(strBuffer, 5, 5, 20, WHITE);
}
