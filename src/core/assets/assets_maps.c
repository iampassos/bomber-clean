#include "assets_maps.h"
#include "asset_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void assets_maps_load_map_textures(MapType map_type) {
  char map_path[100];
  const char **image_path = NULL;
  int size = 0;

  switch (map_type) {
  case MAP_BATTLE_STAGE_1: {
    strcpy(map_path, "assets/sprites/maps/battle_stage_one/");
    static const char *paths[] = {
        "MAP.png",
        "BOMB1.png",
        "BOMB2.png",
        "BOMB3.png",
        "BRICK_DESTRUCTION_1.png",
        "BRICK_DESTRUCTION_2.png",
        "BRICK_DESTRUCTION_3.png",
        "BRICK_DESTRUCTION_4.png",
        "BRICK_DESTRUCTION_5.png",
        "BRICK_DESTRUCTION_6.png",
        "GRASS_SHADOW.png",
        "GRASS.png",
        "BRICK.png",
        "WALL.png",
    };
    image_path = paths;
    size = sizeof(paths) / sizeof(paths[0]);
    break;
  }
  case MAP_PEACE_TOWN: {
    strcpy(map_path, "assets/sprites/maps/peace_town/");
    static const char *paths[] = {
        "MAP.png",
        "BOMB1.png",
        "BOMB2.png",
        "BOMB3.png",
        "BRICK_DESTRUCTION_1.png",
        "BRICK_DESTRUCTION_2.png",
        "BRICK_DESTRUCTION_3.png",
        "BRICK_DESTRUCTION_4.png",
        "BRICK_DESTRUCTION_5.png",
        "BRICK_DESTRUCTION_6.png",
        "GRASS.png",
        "GRASS_SHADOW.png",
        "GRASS_SHADOW_BOMB.png",
        "BRICK.png",
        "BRICK_SHADOW1.png",
        "BRICK_SHADOW2.png",
        "BRICK_SHADOW3.png",
        "BRICK_SHADOW4.png",
        "BRICK1.png",
        "BRICK2.png",
        "BRICK3.png",
        "BRICK4.png",
    };
    image_path = paths;
    size = sizeof(paths) / sizeof(paths[0]);
    break;
  }
  }

  Image images[size];
  asset_manager.assets_maps.map_tiles = malloc(sizeof(Texture2D) * size);

  char path[150];

  sprintf(path, "%s%s", map_path, image_path[0]);
  images[0] = LoadImage(path);
  ImageResizeNN(&images[0], 272 * 4, 208 * 4);
  asset_manager.assets_maps.map_background = LoadTextureFromImage(images[0]);

  for (int i = 1; i <= 3; i++) {
    sprintf(path, "%s%s", map_path, image_path[i]);
    images[i] = LoadImage(path);
    ImageResizeNN(&images[i], TILE_SIZE, TILE_SIZE);
    asset_manager.assets_maps.bomb[i - 1] = LoadTextureFromImage(images[i]);
  }

  for (int i = 4; i <= 9; i++) {
    sprintf(path, "%s%s", map_path, image_path[i]);
    images[i] = LoadImage(path);
    ImageResizeNN(&images[i], TILE_SIZE, TILE_SIZE);
    asset_manager.assets_maps.brick_destruction[i - 4] =
        LoadTextureFromImage(images[i]);
  }

  for (int i = 10; i < size; i++) {
    sprintf(path, "%s%s", map_path, image_path[i]);
    images[i] = LoadImage(path);
    ImageResizeNN(&images[i], TILE_SIZE, TILE_SIZE);
    asset_manager.assets_maps.map_tiles[i] = LoadTextureFromImage(images[i]);
  }

  for (int i = 0; i < size; i++) {
    SetTextureFilter(asset_manager.assets_maps.map_tiles[i],
                     TEXTURE_FILTER_POINT);
    UnloadImage(images[i]);
  }

  assets_maps_load_explosion_textures(map_path);
}

Texture2D *assets_maps_get_map_background_texture() {
  return &asset_manager.assets_maps.map_background;
}

Texture2D *assets_maps_get_map_tiles_textures() {
  return asset_manager.assets_maps.map_tiles;
}

Texture2D *assets_maps_get_bomb_texture(int frame) {
  return &asset_manager.assets_maps.bomb[frame];
}

Texture2D *assets_maps_get_brick_destruction_texture(int frame) {
  return &asset_manager.assets_maps.brick_destruction[frame];
}

void assets_maps_load_explosion_textures(char *map_path) {
  assets_maps_load_explosion_center_textures(map_path);
  assets_maps_load_explosion_middle_textures(map_path);
  assets_maps_load_explosion_final_textures(map_path);
}

void assets_maps_load_explosion_center_textures(char *map_path) {
  const char *paths[5] = {"EXPLOSION_CENTER_1.png", "EXPLOSION_CENTER_2.png",
                          "EXPLOSION_CENTER_3.png", "EXPLOSION_CENTER_4.png",
                          "EXPLOSION_CENTER_5.png"};

  char path[150];

  for (int frame = 0; frame < 5; frame++) {
    sprintf(path, "%s%s", map_path, paths[frame]);
    Image img = LoadImage(path);
    ImageResizeNN(&img, TILE_SIZE, TILE_SIZE);
    asset_manager.assets_maps.explosion_center[frame] =
        LoadTextureFromImage(img);
    SetTextureFilter(asset_manager.assets_maps.explosion_center[frame],
                     TEXTURE_FILTER_POINT);
    UnloadImage(img);
  }
}
void assets_maps_load_explosion_middle_textures(char *map_path) {
  const char *paths[2][5] = {
      {"EXPLOSION_MIDDLE_VERTICAL_1.png", "EXPLOSION_MIDDLE_VERTICAL_2.png",
       "EXPLOSION_MIDDLE_VERTICAL_3.png", "EXPLOSION_MIDDLE_VERTICAL_4.png",
       "EXPLOSION_MIDDLE_VERTICAL_5.png"},
      {"EXPLOSION_MIDDLE_HORIZONTAL_1.png", "EXPLOSION_MIDDLE_HORIZONTAL_2.png",
       "EXPLOSION_MIDDLE_HORIZONTAL_3.png", "EXPLOSION_MIDDLE_HORIZONTAL_4.png",
       "EXPLOSION_MIDDLE_HORIZONTAL_5.png"},
  };

  char path[150];

  for (int dir = 0; dir < 2; dir++) {
    for (int frame = 0; frame < 5; frame++) {
      sprintf(path, "%s%s", map_path, paths[dir][frame]);
      Image img = LoadImage(path);
      ImageResizeNN(&img, TILE_SIZE, TILE_SIZE);
      asset_manager.assets_maps.explosion_middle[dir][frame] =
          LoadTextureFromImage(img);
      SetTextureFilter(asset_manager.assets_maps.explosion_middle[dir][frame],
                       TEXTURE_FILTER_POINT);
      UnloadImage(img);
    }
  }
}

void assets_maps_load_explosion_final_textures(char *map_path) {
  const char *paths[4][5] = {
      {"EXPLOSION_TOP_1.png", "EXPLOSION_TOP_2.png", "EXPLOSION_TOP_3.png",
       "EXPLOSION_TOP_4.png", "EXPLOSION_TOP_5.png"},
      {"EXPLOSION_BOTTOM_1.png", "EXPLOSION_BOTTOM_2.png",
       "EXPLOSION_BOTTOM_3.png", "EXPLOSION_BOTTOM_4.png",
       "EXPLOSION_BOTTOM_5.png"},
      {"EXPLOSION_LEFT_1.png", "EXPLOSION_LEFT_2.png", "EXPLOSION_LEFT_3.png",
       "EXPLOSION_LEFT_4.png", "EXPLOSION_LEFT_5.png"},
      {"EXPLOSION_RIGHT_1.png", "EXPLOSION_RIGHT_2.png",
       "EXPLOSION_RIGHT_3.png", "EXPLOSION_RIGHT_4.png",
       "EXPLOSION_RIGHT_5.png"},

  };

  char path[150];

  for (int dir = 0; dir < 4; dir++) {
    for (int frame = 0; frame < 5; frame++) {
      sprintf(path, "%s%s", map_path, paths[dir][frame]);
      Image img = LoadImage(path);
      ImageResizeNN(&img, TILE_SIZE, TILE_SIZE);
      asset_manager.assets_maps.explosion_final[dir][frame] =
          LoadTextureFromImage(img);
      SetTextureFilter(asset_manager.assets_maps.explosion_final[dir][frame],
                       TEXTURE_FILTER_POINT);
      UnloadImage(img);
    }
  }
}

Texture2D *assets_maps_get_explosion_center_texture(int frame) {
  return &asset_manager.assets_maps.explosion_center[frame];
}

Texture2D *assets_maps_get_explosion_middle_texture(EntityDirection direction,
                                                    int frame) {
  return &asset_manager.assets_maps.explosion_middle
              [direction == DIR_UP || direction == DIR_DOWN ? 0 : 1][frame];
}

Texture2D *assets_maps_get_explosion_final_texture(EntityDirection direction,
                                                   int frame) {
  return &asset_manager.assets_maps.explosion_final[direction][frame];
}
