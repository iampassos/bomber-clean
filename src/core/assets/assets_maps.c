#include "assets_maps.h"
#include "asset_manager.h"
#include "core/assets/assets_enemies.h"
#include "core/map.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

void assets_maps_load_textures(MapType map_type) {
  assets_enemies_load_ballom_textures();

  switch (map_type) {
  case MAP_NORMAL_ZONE:
    assets_maps_load_normal_zone();
    break;
  case MAP_BOMB_ZONE:
    assets_maps_load_bomb_zone();
    break;
  case MAP_JUMP_ZONE:
    assets_maps_load_jump_zone();
    break;
  case MAP_DUEL_ZONE:
    assets_maps_load_duel_zone();
    break;
  case MAP_LIGHT_ZONE:
    assets_maps_load_light_zone();
    break;
  case MAP_SPEED_ZONE:
    assets_maps_load_speed_zone();
    break;
  case MAP_BELT_ZONE:
    assets_maps_load_belt_zone();
    break;
  case MAP_WESTERN_ZONE:
    assets_maps_load_western_zone();
    break;
  }
}

void assets_maps_unload_all() {
  UnloadTexture(asset_manager.assets_maps.background);

  for (int i = 0; i < asset_manager.assets_maps.tile_count; i++)
    UnloadTexture(asset_manager.assets_maps.tiles[i]);

  for (int i = 0; i < 3; i++) {
    UnloadTexture(asset_manager.assets_maps.bomb[i]);
    UnloadTexture(asset_manager.assets_maps.bomb_machine[i]);
  }

  for (int i = 0; i < 6; i++)
    UnloadTexture(asset_manager.assets_maps.brick_destruction[i]);

  for (int i = 0; i < 7; i++)
    UnloadTexture(asset_manager.assets_maps.power_up_explosion[i]);
}

void assets_maps_load_core(char *map_path) {
  Image images[20];
  char path[150];

  sprintf(path, "%sMAP.png", map_path);
  images[0] = LoadImage(path);
  ImageResizeNN(&images[0], 272 * 4, 208 * 4);
  asset_manager.assets_maps.background = LoadTextureFromImage(images[0]);

  for (int i = 0; i < 3; i++) {
    sprintf(path, "%sBOMB%d.png", map_path, i + 1);
    images[i] = LoadImage(path);
    ImageResizeNN(&images[i], TILE_SIZE, TILE_SIZE);
    asset_manager.assets_maps.bomb[i] = LoadTextureFromImage(images[i]);
  }

  for (int i = 0; i < 3; i++) {
    sprintf(path, "%sBOMB_MACHINE%d.png", map_path, i + 1);
    images[i] = LoadImage(path);
    ImageResizeNN(&images[i], TILE_SIZE, TILE_SIZE);
    asset_manager.assets_maps.bomb_machine[i] = LoadTextureFromImage(images[i]);
  }

  for (int i = 0; i < 6; i++) {
    sprintf(path, "%sBRICK_DESTRUCTION_%d.png", map_path, i + 1);
    images[i] = LoadImage(path);
    ImageResizeNN(&images[i], TILE_SIZE, TILE_SIZE);
    asset_manager.assets_maps.brick_destruction[i] =
        LoadTextureFromImage(images[i]);
  }

  for (int i = 0; i < 7; i++) {
    sprintf(path, "%sPOWER_UP_EXPLOSION_%d.png", map_path, i + 1);
    images[i] = LoadImage(path);
    ImageResizeNN(&images[i], TILE_SIZE, TILE_SIZE);
    asset_manager.assets_maps.power_up_explosion[i] =
        LoadTextureFromImage(images[i]);
  }

  for (int i = 0; i < 7; i++)
    UnloadImage(images[i]);
}

void assets_maps_load_normal_zone() {
  char *map_path = "assets/sprites/maps/normal_zone/";

  static const char *paths[] = {
      "GRASS_SHADOW",
      "BRICK",
  };
  int size = sizeof(paths) / sizeof(paths[0]);
  asset_manager.assets_maps.tile_count = size;

  Image images[size];
  asset_manager.assets_maps.tiles = malloc(sizeof(Texture2D) * size);

  assets_maps_load_core(map_path);

  char path[150];

  for (int i = 0; i < size; i++) {
    sprintf(path, "%s%s.png", map_path, paths[i]);
    images[i] = LoadImage(path);
    ImageResizeNN(&images[i], TILE_SIZE, TILE_SIZE);
    asset_manager.assets_maps.tiles[i] = LoadTextureFromImage(images[i]);
  }

  for (int i = 0; i < size; i++) {
    SetTextureFilter(asset_manager.assets_maps.tiles[i], TEXTURE_FILTER_POINT);
    UnloadImage(images[i]);
  }
}

void assets_maps_load_bomb_zone() {
  char *map_path = "assets/sprites/maps/bomb_zone/";

  static const char *paths[] = {
      "GRASS_SHADOW",  "GRASS_SHADOW_BOMB",
      "BRICK",         "BRICK_SHADOW1",
      "BRICK_SHADOW2", "BRICK_SHADOW3",
      "BRICK_SHADOW4", "BRICK1",
      "BRICK2",        "BRICK3",
      "BRICK4",
  };
  int size = sizeof(paths) / sizeof(paths[0]);
  asset_manager.assets_maps.tile_count = size;

  Image images[size];
  asset_manager.assets_maps.tiles = malloc(sizeof(Texture2D) * size);

  assets_maps_load_core(map_path);

  char path[150];

  for (int i = 0; i < size; i++) {
    sprintf(path, "%s%s.png", map_path, paths[i]);
    images[i] = LoadImage(path);
    ImageResizeNN(&images[i], TILE_SIZE, TILE_SIZE);
    asset_manager.assets_maps.tiles[i] = LoadTextureFromImage(images[i]);
  }

  for (int i = 0; i < size; i++) {
    SetTextureFilter(asset_manager.assets_maps.tiles[i], TEXTURE_FILTER_POINT);
    UnloadImage(images[i]);
  }
}

void assets_maps_load_light_zone() {
  char *map_path = "assets/sprites/maps/light_zone/";

  static const char *paths[] = {
      "BRICK1",        "BRICK2",        "BRICK3",        "BRICK4",
      "BRICK5",        "BRICK_SHADOW1", "BRICK_SHADOW2", "BRICK_SHADOW3",
      "BRICK_SHADOW4", "BRICK_SHADOW5",
  };
  int size = sizeof(paths) / sizeof(paths[0]);
  asset_manager.assets_maps.tile_count = size;

  Image images[size];
  asset_manager.assets_maps.tiles = malloc(sizeof(Texture2D) * size);

  assets_maps_load_core(map_path);

  char path[150];

  for (int i = 0; i < size; i++) {
    sprintf(path, "%s%s.png", map_path, paths[i]);
    images[i] = LoadImage(path);
    ImageResizeNN(&images[i], TILE_SIZE, TILE_SIZE);
    asset_manager.assets_maps.tiles[i] = LoadTextureFromImage(images[i]);
  }

  for (int i = 0; i < size; i++) {
    SetTextureFilter(asset_manager.assets_maps.tiles[i], TEXTURE_FILTER_POINT);
    UnloadImage(images[i]);
  }
}

void assets_maps_load_speed_zone() {
  char *map_path = "assets/sprites/maps/speed_zone/";

  static const char *paths[] = {"BRICK1", "BRICK2", "BRICK3", "GRASS_SHADOW"};

  int size = sizeof(paths) / sizeof(paths[0]);
  asset_manager.assets_maps.tile_count = size;

  Image images[size];
  asset_manager.assets_maps.tiles = malloc(sizeof(Texture2D) * size);

  assets_maps_load_core(map_path);

  char path[150];

  for (int i = 0; i < size; i++) {
    sprintf(path, "%s%s.png", map_path, paths[i]);
    images[i] = LoadImage(path);
    ImageResizeNN(&images[i], TILE_SIZE, TILE_SIZE);
    asset_manager.assets_maps.tiles[i] = LoadTextureFromImage(images[i]);
  }

  for (int i = 0; i < size; i++) {
    SetTextureFilter(asset_manager.assets_maps.tiles[i], TEXTURE_FILTER_POINT);
    UnloadImage(images[i]);
  }
}

void assets_maps_load_belt_zone() {
  char *map_path = "assets/sprites/maps/belt_zone/";

  static const char *paths[] = {
      "GRASS_SHADOW", "BRICK1",  "BRICK2",  "BRICK3",   "BRICK4",
      "BRICK5",       "BRICK6",  "BRICK7",  "BRICK8",   "BRICK9",
      "BRICK10",      "BRICK11", "BRICK12", "CAR_LEFT", "CAR_RIGHT"};

  int size = sizeof(paths) / sizeof(paths[0]);
  asset_manager.assets_maps.tile_count = size;

  Image images[size];
  asset_manager.assets_maps.tiles = malloc(sizeof(Texture2D) * size);

  assets_maps_load_core(map_path);

  char path[150];

  for (int i = 0; i < size - 1; i++) {
    sprintf(path, "%s%s.png", map_path, paths[i]);
    images[i] = LoadImage(path);
    ImageResizeNN(&images[i], TILE_SIZE, TILE_SIZE);
    asset_manager.assets_maps.tiles[i] = LoadTextureFromImage(images[i]);
  }

  for (int i = 13; i < size; i++) {
    sprintf(path, "%s%s.png", map_path, paths[i]);
    images[i] = LoadImage(path);
    ImageFormat(&images[i], PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    ImageResizeNN(&images[i], 64, 128);
    ImageColorReplace(&images[i], (Color){104, 112, 80, 255}, BLANK);
    asset_manager.assets_maps.tiles[i] = LoadTextureFromImage(images[i]);
  }

  for (int i = 0; i < size; i++) {
    SetTextureFilter(asset_manager.assets_maps.tiles[i], TEXTURE_FILTER_POINT);
    UnloadImage(images[i]);
  }
}

void assets_maps_load_western_zone() {
  char *map_path = "assets/sprites/maps/western_zone/";

  static const char *paths[] = {"BRICK", "BRICK_SHADOW", "GRASS_SHADOW",
                                "GRASS_SHADOW1"};

  int size = sizeof(paths) / sizeof(paths[0]);
  asset_manager.assets_maps.tile_count = size;

  Image images[size];
  asset_manager.assets_maps.tiles = malloc(sizeof(Texture2D) * size);

  assets_maps_load_core(map_path);

  char path[150];

  for (int i = 0; i < size; i++) {
    sprintf(path, "%s%s.png", map_path, paths[i]);
    images[i] = LoadImage(path);
    ImageResizeNN(&images[i], TILE_SIZE, TILE_SIZE);
    asset_manager.assets_maps.tiles[i] = LoadTextureFromImage(images[i]);
  }

  for (int i = 0; i < size; i++) {
    SetTextureFilter(asset_manager.assets_maps.tiles[i], TEXTURE_FILTER_POINT);
    UnloadImage(images[i]);
  }
}

void assets_maps_load_duel_zone() {
  char *map_path = "assets/sprites/maps/duel_zone/";

  static const char *paths[] = {"GRASS_SHADOW", "BRICK"};
  int size = sizeof(paths) / sizeof(paths[0]);
  asset_manager.assets_maps.tile_count = size;

  Image images[size];
  asset_manager.assets_maps.tiles = malloc(sizeof(Texture2D) * size);

  assets_maps_load_core(map_path);

  char path[150];

  for (int i = 0; i < size; i++) {
    sprintf(path, "%s%s.png", map_path, paths[i]);
    images[i] = LoadImage(path);
    ImageResizeNN(&images[i], TILE_SIZE, TILE_SIZE);
    asset_manager.assets_maps.tiles[i] = LoadTextureFromImage(images[i]);
  }

  for (int i = 0; i < size; i++) {
    SetTextureFilter(asset_manager.assets_maps.tiles[i], TEXTURE_FILTER_POINT);
    UnloadImage(images[i]);
  }
}

void assets_maps_load_jump_zone() {
  char *map_path = "assets/sprites/maps/jump_zone/";

  static const char *paths[] = {
      "BRICK",         "BRICK_LEFT_1",  "BRICK_LEFT_2",  "BRICK_LEFT_3",
      "BRICK_RIGHT_1", "BRICK_RIGHT_2", "BRICK_RIGHT_3",

  };
  int size = sizeof(paths) / sizeof(paths[0]);
  asset_manager.assets_maps.tile_count = size;

  Image images[size];
  asset_manager.assets_maps.tiles = malloc(sizeof(Texture2D) * size);

  assets_maps_load_core(map_path);

  char path[150];

  for (int i = 0; i < size; i++) {
    sprintf(path, "%s%s.png", map_path, paths[i]);
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

Texture2D *assets_maps_get_bomb_machine_texture(int frame) {
  return &asset_manager.assets_maps.bomb_machine[frame];
}

Texture2D *assets_maps_get_brick_destruction_texture(int frame) {
  return &asset_manager.assets_maps.brick_destruction[frame];
}

Texture2D *assets_maps_get_power_up_explosion_texture(int frame) {
  return &asset_manager.assets_maps.power_up_explosion[frame];
}
