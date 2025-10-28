#include "map.h"
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

void map_init() {
  srand((unsigned)time(NULL));

  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      if (i == 0 || j == 0 || i + 1 == GRID_HEIGHT || j + 1 == GRID_WIDTH ||
          (i % 2 == 0 && j % 2 == 0)) {
        state.map.grid[i][j] = TILE_WALL;
      } else
        state.map.grid[i][j] =
            (i != 1 || j != 1) && rand() % 100 < 50 ? TILE_BRICK : TILE_EMPTY;
    }
  }

  state.map.stage = STAGE_ONE;
  state.map.draw = map_draw_one;
  map_load(map_load_one);
}

void map_load(void (*func)(void)) { func(); }

void map_draw(void (*func)(void)) { func(); }

Image *images;
Texture2D *textures;

void map_load_zero() {
  char *image_path[] = {
      "assets/sprites/maps/0/MAP.png",
      "assets/sprites/maps/0/GRASS_SHADOW.png",
      "assets/sprites/maps/0/GRASS.png",
      "assets/sprites/maps/0/BRICK.png",
      "assets/sprites/maps/0/WALL.png",
      "assets/sprites/maps/0/BOMB1.png",
      "assets/sprites/maps/0/BOMB2.png",
      "assets/sprites/maps/0/BOMB3.png",
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

void map_draw_zero() {
  DrawTexture(textures[0], MAP_X_OFFSET - TILE_SIZE, MAP_Y_OFFSET, WHITE);

  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      Texture2D *text = NULL;

      switch (state.map.grid[i][j]) {
      case TILE_EMPTY:
        Bomb *bomb = bomb_find_on_grid_position((GridPosition){j, i});

        if (bomb)
          text = &textures[5 + bomb->animation_step];
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

void map_load_one() {
  char *image_path[] = {
      "assets/sprites/maps/1/MAP.png",
      "assets/sprites/maps/1/GRASS.png",
      "assets/sprites/maps/1/GRASS_SHADOW.png",
      "assets/sprites/maps/1/GRASS_SHADOW_BOMB.png",
      "assets/sprites/maps/1/BRICK.png",
      "assets/sprites/maps/1/BRICK_SHADOW1.png",
      "assets/sprites/maps/1/BRICK_SHADOW2.png",
      "assets/sprites/maps/1/BRICK_SHADOW3.png",
      "assets/sprites/maps/1/BRICK_SHADOW4.png",
      "assets/sprites/maps/1/BRICK1.png",
      "assets/sprites/maps/1/BRICK2.png",
      "assets/sprites/maps/1/BRICK3.png",
      "assets/sprites/maps/1/BRICK4.png",
      "assets/sprites/maps/1/BOMB1.png",
      "assets/sprites/maps/1/BOMB2.png",
      "assets/sprites/maps/1/BOMB3.png",
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

void map_draw_one() {
  DrawTexture(textures[0], MAP_X_OFFSET - TILE_SIZE, MAP_Y_OFFSET, WHITE);

  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      Texture2D *text = NULL;

      switch (state.map.grid[i][j]) {
      case TILE_EMPTY:
        Bomb *bomb = bomb_find_on_grid_position((GridPosition){j, i});

        if (bomb)
          text = &textures[13 + bomb->animation_step];
        else
          text = state.map.grid[i - 1][j] != TILE_EMPTY
                     ? state.map.grid[i - 1][j] == TILE_BRICK ? &textures[3]
                                                              : &textures[2]
                     : NULL;

        break;
      case TILE_BRICK:
        text = state.map.grid[i - 1][j] != TILE_EMPTY ? &textures[5]
                                                      : &textures[9];
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
