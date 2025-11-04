#include "assets_maps.h"
#include "asset_manager.h"
#include "core/assets/assets_enemies.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void assets_maps_load_textures(MapType map_type) {
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

    assets_enemies_load_ballom_textures();
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
  asset_manager.assets_maps.tiles = malloc(sizeof(Texture2D) * size);

  char path[150];

  sprintf(path, "%s%s", map_path, image_path[0]);
  images[0] = LoadImage(path);
  ImageResizeNN(&images[0], 272 * 4, 208 * 4);
  asset_manager.assets_maps.background = LoadTextureFromImage(images[0]);

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
    asset_manager.assets_maps.tiles[i] = LoadTextureFromImage(images[i]);
  }

  for (int i = 0; i < size; i++) {
    SetTextureFilter(asset_manager.assets_maps.tiles[i], TEXTURE_FILTER_POINT);
    UnloadImage(images[i]);
  }
}

Texture2D *assets_maps_get_background_texture() {
  return &asset_manager.assets_maps.background;
}

Texture2D *assets_maps_get_tiles_textures() {
  return asset_manager.assets_maps.tiles;
}

Texture2D *assets_maps_get_bomb_texture(int frame) {
  return &asset_manager.assets_maps.bomb[frame];
}

Texture2D *assets_maps_get_brick_destruction_texture(int frame) {
  return &asset_manager.assets_maps.brick_destruction[frame];
}
