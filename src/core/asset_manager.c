#include "asset_manager.h"
#include "core/map.h"
#include <raylib.h>
#include <stdlib.h>

AssetManager asset_manager = {0};

void asset_manager_init() {}

void asset_manager_load_all() {
  asset_manager_load_player_textures();
  asset_manager_load_hud_textures();
}

void asset_manager_load_player_textures() {
  const char *paths[4][3] = {
      {"assets/sprites/player/UP1.png", "assets/sprites/player/UP2.png",
       "assets/sprites/player/UP3.png"},
      {"assets/sprites/player/DOWN1.png", "assets/sprites/player/DOWN2.png",
       "assets/sprites/player/DOWN3.png"},
      {"assets/sprites/player/LEFT1.png", "assets/sprites/player/LEFT2.png",
       "assets/sprites/player/LEFT3.png"},
      {"assets/sprites/player/RIGHT1.png", "assets/sprites/player/RIGHT2.png",
       "assets/sprites/player/RIGHT3.png"}};

  for (int dir = 0; dir < 4; dir++) {
    for (int frame = 0; frame < 3; frame++) {
      Image img = LoadImage(paths[dir][frame]);
      ImageResizeNN(&img, 64, 88);
      asset_manager.player[dir][frame] = LoadTextureFromImage(img);
      SetTextureFilter(asset_manager.player[dir][frame], TEXTURE_FILTER_POINT);
      UnloadImage(img);
    }
  }
}

Texture2D *asset_manager_get_player_texture(Direction direction, int frame) {
  return &asset_manager.player[direction][frame];
}

void asset_manager_load_map_textures(MapType map_type) {
  const char **image_path = NULL;
  int size = 0;

  switch (map_type) {
  case MAP_BATTLE_STAGE_1: {
    static const char *paths[] = {
        "assets/sprites/maps/battle_stage_one/MAP.png",
        "assets/sprites/maps/battle_stage_one/BOMB1.png",
        "assets/sprites/maps/battle_stage_one/BOMB2.png",
        "assets/sprites/maps/battle_stage_one/BOMB3.png",
        "assets/sprites/maps/battle_stage_one/GRASS_SHADOW.png",
        "assets/sprites/maps/battle_stage_one/GRASS.png",
        "assets/sprites/maps/battle_stage_one/BRICK.png",
        "assets/sprites/maps/battle_stage_one/WALL.png",
    };
    image_path = paths;
    size = sizeof(paths) / sizeof(paths[0]);
    break;
  }
  case MAP_STAGE_1: {
    static const char *paths[] = {
        "assets/sprites/maps/stage_one/MAP.png",
        "assets/sprites/maps/stage_one/BOMB1.png",
        "assets/sprites/maps/stage_one/BOMB2.png",
        "assets/sprites/maps/stage_one/BOMB3.png",
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
    };
    image_path = paths;
    size = sizeof(paths) / sizeof(paths[0]);
    break;
  }
  }

  Image images[size];
  asset_manager.map_tiles = malloc(sizeof(Texture2D) * size);

  images[0] = LoadImage(image_path[0]);
  ImageResizeNN(&images[0], 272 * 4, 208 * 4);
  asset_manager.map_background = LoadTextureFromImage(images[0]);
  UnloadImage(images[0]);

  for (int i = 1; i <= 3; i++) {
    images[i] = LoadImage(image_path[i]);
    ImageResizeNN(&images[i], TILE_SIZE, TILE_SIZE);
    asset_manager.bomb[i - 1] = LoadTextureFromImage(images[i]);
    SetTextureFilter(asset_manager.map_tiles[i], TEXTURE_FILTER_POINT);
    UnloadImage(images[i]);
  }

  for (int i = 4; i < size; i++) {
    images[i] = LoadImage(image_path[i]);
    ImageResizeNN(&images[i], TILE_SIZE, TILE_SIZE);
    asset_manager.map_tiles[i] = LoadTextureFromImage(images[i]);
    SetTextureFilter(asset_manager.map_tiles[i], TEXTURE_FILTER_POINT);
    UnloadImage(images[i]);
  }
}

Texture2D *asset_manager_get_map_background_texture() {
  return &asset_manager.map_background;
}

Texture2D *asset_manager_get_map_tiles_textures() {
  return asset_manager.map_tiles;
}

Texture2D *asset_manager_get_bomb_texture(int frame) {
  return &asset_manager.bomb[frame];
}

void asset_manager_load_hud_textures() {
  asset_manager.hud_top = LoadTexture("assets/hud/TOP_HUD.png");
}

Texture2D *asset_manager_get_hud_texture() { return &asset_manager.hud_top; }
