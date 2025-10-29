#include "map.h"
#include "animation.h"
#include "bomb.h"
#include "common.h"
#include "state.h"
#include <raylib.h>
#include <stdlib.h>

const Color TILE_COLORS[3] = {
    [TILE_EMPTY] = (Color){17, 92, 51, 255},
    [TILE_WALL] = (Color){101, 101, 101, 255},
    [TILE_BRICK] = (Color){58, 58, 58, 255},
};

Image *images;
Texture2D *textures;

GridPosition map_get_grid_position(Vector2 position) {
  return (GridPosition){.col = (position.x - MAP_X_OFFSET) / TILE_SIZE,
                        .row = (position.y - MAP_Y_OFFSET) / TILE_SIZE};
}

Vector2 map_get_vector_from_grid_center(GridPosition position) {
  return (Vector2){.x = MAP_X_OFFSET + position.col * TILE_SIZE + TILE_SIZE / 2,
                   .y =
                       MAP_Y_OFFSET + position.row * TILE_SIZE + TILE_SIZE / 2};
}

Vector2 map_get_vector_from_grid(GridPosition position) {
  return (Vector2){.x = MAP_X_OFFSET + position.col * TILE_SIZE,
                   .y = MAP_Y_OFFSET + position.row * TILE_SIZE};
}

void map_init(MapType type) {
  srand((unsigned)time(NULL));

  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      if (i == 0 || j == 0 || i + 1 == GRID_HEIGHT || j + 1 == GRID_WIDTH ||
          (i % 2 == 0 && j % 2 == 0)) {
        state.map.grid[i][j] = TILE_WALL;
      } else
        state.map.grid[i][j] =
            (i != 1 || j != 1) && rand() % 100 < 40 ? TILE_BRICK : TILE_EMPTY;
    }
  }

  switch (type) {
  case MAP_BATTLE_STAGE_1:
    state.map.stage = MAP_BATTLE_STAGE_1;
    state.map.draw = map_draw_battle_stage_one;
    state.map.update = map_update_battle_stage_one;
    map_load(map_load_battle_stage_one);
    break;
  case MAP_STAGE_1:
    state.map.stage = MAP_STAGE_1;
    state.map.draw = map_draw_stage_one;
    state.map.update = map_update_stage_one;
    map_load(map_load_stage_one);
    break;
  }
}

void map_load(void (*func)(void)) { func(); }

void map_draw(void (*func)(void)) { func(); }

void map_update(void (*func)(void)) { func(); }

void map_load_battle_stage_one() {
  char *image_path[] = {
      "assets/sprites/maps/battle_stage_one/MAP.png",
      "assets/sprites/maps/battle_stage_one/GRASS_SHADOW.png",
      "assets/sprites/maps/battle_stage_one/GRASS.png",
      "assets/sprites/maps/battle_stage_one/BRICK.png",
      "assets/sprites/maps/battle_stage_one/WALL.png",
      "assets/sprites/maps/battle_stage_one/BOMB1.png",
      "assets/sprites/maps/battle_stage_one/BOMB2.png",
      "assets/sprites/maps/battle_stage_one/BOMB3.png",
  };

  int size = sizeof(image_path) / sizeof(image_path[0]);

  images = malloc(sizeof(Image) * size);
  textures = malloc(sizeof(Texture2D) * size);

  for (int i = 0; i < size; i++) {
    if (i == 0) {
      images[i] = LoadImage(image_path[i]);
      ImageResizeNN(&images[i], 272 * 4, 208 * 4);
    } else {
      images[i] = LoadImage(image_path[i]);
      ImageResizeNN(&images[i], TILE_SIZE, TILE_SIZE);
    }

    textures[i] = LoadTextureFromImage(images[i]);
    SetTextureFilter(textures[i], TEXTURE_FILTER_POINT);
    UnloadImage(images[i]);
  }
}

void map_update_battle_stage_one() {}

void map_draw_battle_stage_one() {
  DrawTexture(textures[0], MAP_X_OFFSET - TILE_SIZE, MAP_Y_OFFSET, WHITE);

  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      Texture2D *text = NULL;

      switch (state.map.grid[i][j]) {
      case TILE_EMPTY:
        Bomb *bomb = bomb_find_on_grid_position((GridPosition){j, i});

        if (bomb)
          text = &textures[5 + bomb->animation.current_step];
        else
          text = state.map.grid[i - 1][j] != TILE_EMPTY ? &textures[1]
                                                        : &textures[2];
        break;
      case TILE_BRICK:
        text = &textures[3];
        break;
      case TILE_WALL:
        text = &textures[4];
        break;
      }

      if (text != NULL)
        DrawTexture(*text, MAP_X_OFFSET + j * TILE_SIZE,
                    MAP_Y_OFFSET + i * TILE_SIZE, WHITE);
    }
  }
}

Animation brick_animation;

void map_update_stage_one() { animation_update(&brick_animation); }

void map_load_stage_one() {
  char *image_path[] = {
      "assets/sprites/maps/stage_one/MAP.png",
      "assets/sprites/maps/stage_one/GRASS.png",
      "assets/sprites/maps/stage_one/GRASS_SHADOW.png",
      "assets/sprites/maps/stage_one/GRASS_SHADOW_BOMB.png",
      "assets/sprites/maps/stage_one/BRICK.png",
      "assets/sprites/maps/stage_one/BRICK_SHADOW1.png",
      "assets/sprites/maps/stage_one/BRICK_SHADOW2.png",
      "assets/sprites/maps/stage_one/BRICK_SHADOW3.png",
      "assets/sprites/maps/stage_one/BRICK_SHADOW4.png",
      "assets/sprites/maps/stage_one/BRICK1.png",
      "assets/sprites/maps/stage_one/BRICK2.png",
      "assets/sprites/maps/stage_one/BRICK3.png",
      "assets/sprites/maps/stage_one/BRICK4.png",
      "assets/sprites/maps/stage_one/BOMB1.png",
      "assets/sprites/maps/stage_one/BOMB2.png",
      "assets/sprites/maps/stage_one/BOMB3.png",
  };

  int size = sizeof(image_path) / sizeof(image_path[0]);

  images = malloc(sizeof(Image) * size);
  textures = malloc(sizeof(Texture2D) * size);

  for (int i = 0; i < size; i++) {
    if (i == 0) {
      images[i] = LoadImage(image_path[i]);
      ImageResizeNN(&images[i], 272 * 4, 208 * 4);
    } else {
      images[i] = LoadImage(image_path[i]);
      ImageResizeNN(&images[i], TILE_SIZE, TILE_SIZE);
    }

    textures[i] = LoadTextureFromImage(images[i]);
    SetTextureFilter(textures[i], TEXTURE_FILTER_POINT);
    UnloadImage(images[i]);
  }

  brick_animation = animation_new(4, 0.1f, 1, NULL, NULL, NULL);
}

void map_draw_stage_one() {
  DrawTexture(textures[0], MAP_X_OFFSET - TILE_SIZE, MAP_Y_OFFSET, WHITE);

  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      Texture2D *text = NULL;

      switch (state.map.grid[i][j]) {
      case TILE_EMPTY:
        Bomb *bomb = bomb_find_on_grid_position((GridPosition){j, i});

        if (bomb)
          text = &textures[13 + bomb->animation.current_step];
        else
          text = state.map.grid[i - 1][j] != TILE_EMPTY
                     ? state.map.grid[i - 1][j] == TILE_BRICK ? &textures[3]
                                                              : &textures[2]
                     : NULL;

        break;
      case TILE_BRICK:
        text = state.map.grid[i - 1][j] != TILE_EMPTY
                   ? &textures[5 + brick_animation.current_step]
                   : &textures[9 + brick_animation.current_step];
        break;

      case TILE_WALL:
        break;
      }

      if (text != NULL)
        DrawTexture(*text, MAP_X_OFFSET + j * TILE_SIZE,
                    MAP_Y_OFFSET + i * TILE_SIZE, WHITE);
    }
  }
}
