#include "asset_manager.h"
#include "core/common.h"
#include "entities/entity.h"
#include <raylib.h>
#include <stdlib.h>

AssetManager asset_manager = {0};

void asset_manager_init() {}

void asset_manager_load_all() {
  asset_manager_load_player_textures();
  asset_manager_load_hud_textures();
  asset_manager_load_power_ups_textures();
  asset_manager_load_explosion_textures();
}

void asset_manager_load_explosion_textures() {
  asset_manager_load_explosion_center_textures();
  asset_manager_load_explosion_middle_textures();
  asset_manager_load_explosion_final_textures();
}

void asset_manager_load_explosion_center_textures() {
  const char *paths[5] = {"assets/sprites/explosion/EXPLOSION_CENTER_1.png",
                          "assets/sprites/explosion/EXPLOSION_CENTER_2.png",
                          "assets/sprites/explosion/EXPLOSION_CENTER_3.png",
                          "assets/sprites/explosion/EXPLOSION_CENTER_4.png",
                          "assets/sprites/explosion/EXPLOSION_CENTER_5.png"};

  for (int frame = 0; frame < 5; frame++) {
    Image img = LoadImage(paths[frame]);
    ImageResizeNN(&img, TILE_SIZE, TILE_SIZE);
    asset_manager.explosion_center[frame] = LoadTextureFromImage(img);
    SetTextureFilter(asset_manager.explosion_center[frame],
                     TEXTURE_FILTER_POINT);
    UnloadImage(img);
  }
}
void asset_manager_load_explosion_middle_textures() {
  const char *paths[2][5] = {
      {"assets/sprites/explosion/EXPLOSION_MIDDLE_VERTICAL_1.png",
       "assets/sprites/explosion/EXPLOSION_MIDDLE_VERTICAL_2.png",
       "assets/sprites/explosion/EXPLOSION_MIDDLE_VERTICAL_3.png",
       "assets/sprites/explosion/EXPLOSION_MIDDLE_VERTICAL_4.png",
       "assets/sprites/explosion/EXPLOSION_MIDDLE_VERTICAL_5.png"},
      {"assets/sprites/explosion/EXPLOSION_MIDDLE_HORIZONTAL_1.png",
       "assets/sprites/explosion/EXPLOSION_MIDDLE_HORIZONTAL_2.png",
       "assets/sprites/explosion/EXPLOSION_MIDDLE_HORIZONTAL_3.png",
       "assets/sprites/explosion/EXPLOSION_MIDDLE_HORIZONTAL_4.png",
       "assets/sprites/explosion/EXPLOSION_MIDDLE_HORIZONTAL_5.png"},
  };

  for (int dir = 0; dir < 2; dir++) {
    for (int frame = 0; frame < 5; frame++) {
      Image img = LoadImage(paths[dir][frame]);
      ImageResizeNN(&img, TILE_SIZE, TILE_SIZE);
      asset_manager.explosion_middle[dir][frame] = LoadTextureFromImage(img);
      SetTextureFilter(asset_manager.explosion_middle[dir][frame],
                       TEXTURE_FILTER_POINT);
      UnloadImage(img);
    }
  }
}

void asset_manager_load_explosion_final_textures() {
  const char *paths[4][5] = {
      {"assets/sprites/explosion/EXPLOSION_TOP_1.png",
       "assets/sprites/explosion/EXPLOSION_TOP_2.png",
       "assets/sprites/explosion/EXPLOSION_TOP_3.png",
       "assets/sprites/explosion/EXPLOSION_TOP_4.png",
       "assets/sprites/explosion/EXPLOSION_TOP_5.png"},
      {"assets/sprites/explosion/EXPLOSION_BOTTOM_1.png",
       "assets/sprites/explosion/EXPLOSION_BOTTOM_2.png",
       "assets/sprites/explosion/EXPLOSION_BOTTOM_3.png",
       "assets/sprites/explosion/EXPLOSION_BOTTOM_4.png",
       "assets/sprites/explosion/EXPLOSION_BOTTOM_5.png"},
      {"assets/sprites/explosion/EXPLOSION_LEFT_1.png",
       "assets/sprites/explosion/EXPLOSION_LEFT_2.png",
       "assets/sprites/explosion/EXPLOSION_LEFT_3.png",
       "assets/sprites/explosion/EXPLOSION_LEFT_4.png",
       "assets/sprites/explosion/EXPLOSION_LEFT_5.png"},
      {"assets/sprites/explosion/EXPLOSION_RIGHT_1.png",
       "assets/sprites/explosion/EXPLOSION_RIGHT_2.png",
       "assets/sprites/explosion/EXPLOSION_RIGHT_3.png",
       "assets/sprites/explosion/EXPLOSION_RIGHT_4.png",
       "assets/sprites/explosion/EXPLOSION_RIGHT_5.png"},

  };

  for (int dir = 0; dir < 4; dir++) {
    for (int frame = 0; frame < 5; frame++) {
      Image img = LoadImage(paths[dir][frame]);
      ImageResizeNN(&img, TILE_SIZE, TILE_SIZE);
      asset_manager.explosion_final[dir][frame] = LoadTextureFromImage(img);
      SetTextureFilter(asset_manager.explosion_final[dir][frame],
                       TEXTURE_FILTER_POINT);
      UnloadImage(img);
    }
  }
}

Texture2D *asset_manager_get_explosion_center_texture(int frame) {
  return &asset_manager.explosion_center[frame];
}

Texture2D *asset_manager_get_explosion_middle_texture(EntityDirection direction,
                                                      int frame) {
  return &asset_manager.explosion_middle
              [direction == DIR_UP || direction == DIR_DOWN ? 0 : 1][frame];
}

Texture2D *asset_manager_get_explosion_final_texture(EntityDirection direction,
                                                     int frame) {
  return &asset_manager.explosion_final[direction][frame];
}

void asset_manager_load_power_ups_textures() {
  const char *paths[3] = {
      "assets/sprites/power_ups/LIFE.png",
      "assets/sprites/power_ups/SPEED_UP.png",
      "assets/sprites/power_ups/BOMB.png",
  };

  for (int frame = 0; frame < 3; frame++) {
    Image img = LoadImage(paths[frame]);
    ImageResizeNN(&img, TILE_SIZE, TILE_SIZE);
    asset_manager.power_ups[frame] = LoadTextureFromImage(img);
    SetTextureFilter(asset_manager.power_ups[frame], TEXTURE_FILTER_POINT);
    UnloadImage(img);
  }
}

Texture2D *asset_manager_get_power_up_texture(PowerUpType type) {
  return &asset_manager.power_ups[type];
}

void asset_manager_load_player_textures() {
  asset_manager_load_player_walk_textures();
  asset_manager_load_player_death_textures();
}

void asset_manager_load_player_walk_textures() {
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
      asset_manager.player_walk[dir][frame] = LoadTextureFromImage(img);
      SetTextureFilter(asset_manager.player_walk[dir][frame],
                       TEXTURE_FILTER_POINT);
      UnloadImage(img);
    }
  }
}

void asset_manager_load_player_death_textures() {
  const char *paths[7] = {
      "assets/sprites/player/PLAYER_DEATH_1.png",
      "assets/sprites/player/PLAYER_DEATH_2.png",
      "assets/sprites/player/PLAYER_DEATH_3.png",
      "assets/sprites/player/PLAYER_DEATH_4.png",
      "assets/sprites/player/PLAYER_DEATH_5.png",
      "assets/sprites/player/PLAYER_DEATH_6.png",
      "assets/sprites/player/PLAYER_DEATH_7.png",
  };

  for (int frame = 0; frame < 7; frame++) {
    Image img = LoadImage(paths[frame]);
    ImageResizeNN(&img, 64, 88);
    asset_manager.player_death[frame] = LoadTextureFromImage(img);
    SetTextureFilter(asset_manager.player_death[frame], TEXTURE_FILTER_POINT);
    UnloadImage(img);
  }
}

Texture2D *asset_manager_get_player_walk_texture(EntityDirection direction,
                                                 int frame) {
  return &asset_manager.player_walk[direction][frame];
}

Texture2D *asset_manager_get_player_death_texture(int frame) {
  return &asset_manager.player_death[frame];
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
        "assets/sprites/maps/battle_stage_one/BRICK_DESTRUCTION_1.png",
        "assets/sprites/maps/battle_stage_one/BRICK_DESTRUCTION_2.png",
        "assets/sprites/maps/battle_stage_one/BRICK_DESTRUCTION_3.png",
        "assets/sprites/maps/battle_stage_one/BRICK_DESTRUCTION_4.png",
        "assets/sprites/maps/battle_stage_one/BRICK_DESTRUCTION_5.png",
        "assets/sprites/maps/battle_stage_one/BRICK_DESTRUCTION_6.png",
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
        "assets/sprites/maps/stage_one/BRICK_DESTRUCTION_1.png",
        "assets/sprites/maps/stage_one/BRICK_DESTRUCTION_2.png",
        "assets/sprites/maps/stage_one/BRICK_DESTRUCTION_3.png",
        "assets/sprites/maps/stage_one/BRICK_DESTRUCTION_4.png",
        "assets/sprites/maps/stage_one/BRICK_DESTRUCTION_5.png",
        "assets/sprites/maps/stage_one/BRICK_DESTRUCTION_6.png",
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
        "assets/sprites/maps/stage_one/EXPLOSION_CENTER.png",
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

  for (int i = 1; i <= 3; i++) {
    images[i] = LoadImage(image_path[i]);
    ImageResizeNN(&images[i], TILE_SIZE, TILE_SIZE);
    asset_manager.bomb[i - 1] = LoadTextureFromImage(images[i]);
  }

  for (int i = 4; i <= 9; i++) {
    images[i] = LoadImage(image_path[i]);
    ImageResizeNN(&images[i], TILE_SIZE, TILE_SIZE);
    asset_manager.brick_destruction[i - 4] = LoadTextureFromImage(images[i]);
  }

  for (int i = 10; i < size; i++) {
    images[i] = LoadImage(image_path[i]);
    ImageResizeNN(&images[i], TILE_SIZE, TILE_SIZE);
    asset_manager.map_tiles[i] = LoadTextureFromImage(images[i]);
  }

  for (int i = 0; i < size; i++) {
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

Texture2D *asset_manager_get_brick_destruction_texture(int frame) {
  return &asset_manager.brick_destruction[frame];
}

Texture2D *asset_manager_get_explosion_texture(int frame) {
  return &asset_manager.map_tiles[frame];
}

void asset_manager_load_hud_textures() {
  asset_manager.hud_top = LoadTexture("assets/hud/TOP_HUD.png");
}

Texture2D *asset_manager_get_hud_texture() { return &asset_manager.hud_top; }
