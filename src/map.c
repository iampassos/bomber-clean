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
  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      if (i == 0 || j == 0 || i + 1 == GRID_HEIGHT || j + 1 == GRID_WIDTH ||
          (i % 2 == 0 && j % 2 == 0))
        state.map.grid[i][j] = TILE_WALL;
      else
        state.map.grid[i][j] = TILE_EMPTY;
    }
  }

  state.map.stage = FIRST;
  state.map.draw = map_draw_first;

  map_load(map_load_first);
}

void map_load(void (*func)(void)) { func(); }

void map_draw(void (*func)(void)) { func(); }

Image *images;
Texture2D *textures;

int stage[13][15] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                     {1, 0, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 0, 1},
                     {1, 0, 1, 2, 1, 2, 1, 2, 1, 0, 1, 2, 1, 0, 1},
                     {1, 2, 2, 0, 2, 2, 2, 0, 2, 2, 0, 2, 2, 2, 1},
                     {1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1},
                     {1, 0, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 0, 2, 1},
                     {1, 2, 1, 0, 1, 2, 1, 0, 1, 2, 1, 0, 1, 2, 1},
                     {1, 2, 2, 2, 2, 0, 2, 2, 0, 2, 2, 2, 2, 0, 1},
                     {1, 0, 1, 2, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1},
                     {1, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 1},
                     {1, 2, 1, 0, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 1},
                     {1, 0, 2, 2, 2, 0, 2, 0, 2, 2, 2, 2, 0, 0, 1},
                     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

void map_load_first() {
  char *image_path[] = {
      "assets/sprites/maps/1/BACKGROUND.png",
      "assets/sprites/maps/1/GRASS_SHADOW.png",
      "assets/sprites/maps/1/GRASS.png",
      "assets/sprites/maps/1/BRICK.png",
      "assets/sprites/maps/1/WALL.png",
      "assets/sprites/maps/1/BOMB1.png",
      "assets/sprites/maps/1/BOMB2.png",
      "assets/sprites/maps/1/BOMB3.png",
  };

  images = malloc(sizeof(Image) * 8);
  textures = malloc(sizeof(Texture2D) * 8);

  for (int i = 0; i < 8; i++) {
    images[i] = LoadImage(image_path[i]);
    ImageResizeNN(&images[i], TILE_SIZE, TILE_SIZE);
    textures[i] = LoadTextureFromImage(images[i]);
    SetTextureFilter(textures[i], TEXTURE_FILTER_POINT);
    UnloadImage(images[i]);
  }

  // for (int i = 0; i < GRID_HEIGHT; i++) {
  //   for (int j = 0; j < GRID_WIDTH; j++) {
  //     state.map.grid[i][j] = stage[i][j];
  //   }
  // }
}

void map_draw_first() {
  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      Texture2D text;
      switch (state.map.grid[i][j]) {
      case TILE_EMPTY:
        text =
            state.map.grid[i - 1][j] != TILE_EMPTY ? textures[1] : textures[2];

        Bomb *bomb = bomb_find_on_grid_position((GridPosition){j, i});

        if (bomb) {
          text = textures[5 + bomb->animation_step];
        }
        break;
      case TILE_BRICK:
        text = textures[3];
        break;
      case TILE_WALL:
        text = textures[4];
        break;
      }

      DrawTexture(text, MAP_X_OFFSET + j * TILE_SIZE,
                  MAP_Y_OFFSET + i * TILE_SIZE, WHITE);
    }
  }
}
