#include "player.h"
#include "animation.h"
#include "bomb.h"
#include "common.h"
#include "controller.h"
#include "map.h"
#include <SDL2/SDL_gamecontroller.h>
#include <math.h>
#include <raylib.h>
#include <state.h>

#define ANIMATION_STEP_MS 500
#define HEIGHT_TOLERANCE 28.5f

const char *PLAYER_IMAGES_PATH[4][3] = {
    {
        "assets/sprites/player/UP1.png",
        "assets/sprites/player/UP2.png",
        "assets/sprites/player/UP3.png",
    },
    {
        "assets/sprites/player/DOWN1.png",
        "assets/sprites/player/DOWN2.png",
        "assets/sprites/player/DOWN3.png",
    },
    {
        "assets/sprites/player/LEFT1.png",
        "assets/sprites/player/LEFT2.png",
        "assets/sprites/player/LEFT3.png",
    },
    {
        "assets/sprites/player/RIGHT1.png",
        "assets/sprites/player/RIGHT2.png",
        "assets/sprites/player/RIGHT3.png",
    },
};

Image PLAYER_IMAGES[4][3];
Texture2D PLAYER_TEXTURES[4][3];

Vector2 player_get_vector_from_grid_position(Player *player, GridPosition pos) {
  Vector2 center = map_get_vector_from_grid_center(pos);
  return (Vector2){center.x - player->width / 2,
                   center.y - player->height / 2 - HEIGHT_TOLERANCE};
}

GridPosition player_get_grid_position(Player *player) {
  Vector2 feet_position = (Vector2){
      player->position.x + player->width / 2.0f,
      player->position.y + (player->direction == UP
                                ? player->height * 1.1f
                                : player->height * 0.60f + HEIGHT_TOLERANCE)};
  GridPosition pos = map_get_grid_position(feet_position);
  return pos;
}

void player_init() {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 3; j++) {
      PLAYER_IMAGES[i][j] = LoadImage(PLAYER_IMAGES_PATH[i][j]);
      ImageResizeNN(&PLAYER_IMAGES[i][j], 64, 88);
      PLAYER_TEXTURES[i][j] = LoadTextureFromImage(PLAYER_IMAGES[i][j]);
      SetTextureFilter(PLAYER_TEXTURES[i][j], TEXTURE_FILTER_POINT);
      UnloadImage(PLAYER_IMAGES[i][j]);
    }
}

void player_new(int id, Vector2 position, float width, float height) {
  Player *player = &state.players.entries[state.players.count++];
  player->id = id;
  player->width = width;
  player->height = height;
  player->direction = DOWN;
  player->state = IDLE;
  player->bomb_capacity = 3;
  player->alive = 1;
  player->speed = DEFAULT_SPEED;
  player->walk_animation = animation_new(3, 0.25f, 1, NULL, NULL, NULL);

  GridPosition pos = map_get_grid_position(position);
  pos.col = fmax(1, fmin(pos.col, GRID_WIDTH - 2));
  pos.row = fmax(1, fmin(pos.row, GRID_HEIGHT - 2));

  if (state.map.grid[pos.row][pos.col] == TILE_EMPTY) {
    player->position = player_get_vector_from_grid_position(player, pos);
    return;
  }

  for (int r = pos.col; r < GRID_HEIGHT - 1; r++) {
    for (int c = pos.row; c < GRID_WIDTH - 1; c++) {
      if (state.map.grid[r][c] == TILE_EMPTY) {
        player->position =
            player_get_vector_from_grid_position(player, (GridPosition){c, r});
        return;
      }
    }
  }

  player->position =
      player_get_vector_from_grid_position(player, (GridPosition){1, 1});
}

int player_can_move(Vector2 projected, float width, float height) {
  float height_text = HEIGHT_TOLERANCE;

  int left = (projected.x - MAP_X_OFFSET) / TILE_SIZE;
  int right = (projected.x + width - MAP_X_OFFSET) / TILE_SIZE;
  int top = (projected.y + height_text - MAP_Y_OFFSET) / TILE_SIZE;
  int bottom = (projected.y + height + height_text - MAP_Y_OFFSET) / TILE_SIZE;

  left = fmax(0, fmin(left, GRID_WIDTH - 1));
  right = fmax(0, fmin(right, GRID_WIDTH - 1));
  top = fmax(0, fmin(top, GRID_HEIGHT - 1));
  bottom = fmax(0, fmin(bottom, GRID_HEIGHT - 1));

  for (int row = top; row <= bottom; row++)
    for (int col = left; col <= right; col++)
      if (state.map.grid[row][col] != TILE_EMPTY)
        return 0;

  return 1;
}

void player_update(Player *player, float x, float y) {
  Vector2 projected = player->position;

  if (x)
    projected.x = fmax(MAP_X_OFFSET, player->position.x + player->speed * x);

  if (y)
    projected.y = fmax(MAP_Y_OFFSET, player->position.y + player->speed * y);

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
    player->walk_animation.current_step = 1;
  }

  player->position = new_pos;
}

float last = 0;

void player_update_all() {
  SDL_GameControllerUpdate();

  SDL_GameController *controller = controllers[0];
  ControllerInput input = controller_input(controller);

  for (int i = 0; i < state.players.count; i++) {
    Player *p = &state.players.entries[i];

    if (p->state == RUNNING)
      animation_update(&p->walk_animation);

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

    if (IsKeyDown(KEY_SPACE)) {
      Bombs *bombs = &state.bombs[i];
      if (bombs->current_length < state.players.entries[i].bomb_capacity &&
          GetTime() - last > 0.25f) {
        GridPosition pos = player_get_grid_position(p);
        bomb_insert(bombs, pos);
        last = GetTime();
      }
    }
  }
}

void player_debug_draw(Player *p) {
  GridPosition pos = player_get_grid_position(p);
  TileType tile = state.map.grid[pos.row][pos.col];
  char strBuffer[1000];
  snprintf(strBuffer, sizeof(strBuffer),
           "Player debug\n"
           "id: %d\n"
           "position: (%.2f, %.2f)\n"
           "grid: (%d, %d)\n"
           "width: %.2f\n"
           "height: %.2f\n"
           "direction: %s\n"
           "state: %s\n"
           "bomb-capacity: %d\n"
           "bombs: %d\n"
           "speed: %.2f\n"
           "alive: %s\n"
           "animation-step: %d\n"
           "standing-on: %s",
           p->id, p->position.x, p->position.y, pos.col, pos.row, p->width,
           p->height,
           p->direction == UP     ? "UP"
           : p->direction == DOWN ? "DOWN"
           : p->direction == LEFT ? "LEFT"
                                  : "RIGHT",
           p->state == IDLE      ? "IDLE"
           : p->state == RUNNING ? "RUNNING"
                                 : "DEAD",
           p->bomb_capacity, state.bombs[p->id].current_length, p->speed,
           p->alive ? "yes" : "no", p->walk_animation.current_step,
           tile == TILE_EMPTY   ? "EMPTY"
           : tile == TILE_WALL  ? "WALL"
           : tile == TILE_BRICK ? "BRICK"
                                : "BOMB");

  Vector2 textSize = MeasureTextEx(GetFontDefault(), strBuffer, 20, 1.0f);

  float x = 15;
  float y = SCREEN_HEIGHT / 2.0f - textSize.y / 2.0f;

  DrawRectangle(x, y, textSize.x + 10, textSize.y + 10,
                (Color){196, 196, 196, 200});

  DrawTextEx(GetFontDefault(), strBuffer, (Vector2){x, y}, 20, 1.0f, BLACK);

  Vector2 grid = map_get_vector_from_grid(pos);

  DrawRectangle(grid.x, grid.y, TILE_SIZE, TILE_SIZE,
                (Color){128, 128, 128, 128});
}
