#include "asset_manager.h"
#include "core/common.h"
#include "core/map.h"
#include "entities/entity.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AssetManager asset_manager = {0};

void asset_manager_init() {}

void asset_manager_load_all() {
  asset_manager_load_player_textures();
  asset_manager_load_hud_textures();
  asset_manager_load_power_ups_textures();
}

void asset_manager_load_power_ups_textures() {
  char *power_up_path = "assets/sprites/power_ups/";

  const char *paths[6][2] = {
      {
          "LIFE_1.png",
          "LIFE_2.png",
      },
      {
          "SPEED_UP_1.png",
          "SPEED_UP_2.png",
      },
      {
          "BOMB_1.png",
          "BOMB_2.png",
      },
      {
          "RADIUS_1.png",
          "RADIUS_2.png",
      },
      {
          "MAXIMUM_RADIUS_1.png",
          "MAXIMUM_RADIUS_2.png",
      },
      {
          "INVENCIBLE_1.png",
          "INVENCIBLE_2.png",
      },
  };

  char path[100];

  for (int power_up = 0; power_up < 6; power_up++) {
    for (int frame = 0; frame < 2; frame++) {
      sprintf(path, "%s%s", power_up_path, paths[power_up][frame]);
      Image img = LoadImage(path);
      ImageResizeNN(&img, TILE_SIZE, TILE_SIZE);
      asset_manager.power_ups[power_up][frame] = LoadTextureFromImage(img);
      SetTextureFilter(asset_manager.power_ups[power_up][frame],
                       TEXTURE_FILTER_POINT);
      UnloadImage(img);
    }
  }
}

Texture2D *asset_manager_get_power_up_texture(PowerUpType type, int frame) {
  return &asset_manager.power_ups[type][frame];
}

void asset_manager_load_player_textures() {
  asset_manager_load_player_walk_textures();
  asset_manager_load_player_walk_white_textures();
  asset_manager_load_player_death_textures();
}

void asset_manager_load_player_walk_white_textures() {
  const char *paths[4][3] = {{"assets/sprites/player/UP1_WHITE.png",
                              "assets/sprites/player/UP2_WHITE.png",
                              "assets/sprites/player/UP3_WHITE.png"},
                             {"assets/sprites/player/DOWN1_WHITE.png",
                              "assets/sprites/player/DOWN2_WHITE.png",
                              "assets/sprites/player/DOWN3_WHITE.png"},
                             {"assets/sprites/player/LEFT1_WHITE.png",
                              "assets/sprites/player/LEFT2_WHITE.png",
                              "assets/sprites/player/LEFT3_WHITE.png"},
                             {"assets/sprites/player/RIGHT1_WHITE.png",
                              "assets/sprites/player/RIGHT2_WHITE.png",
                              "assets/sprites/player/RIGHT3_WHITE.png"}};

  for (int dir = 0; dir < 4; dir++) {
    for (int frame = 0; frame < 3; frame++) {
      Image img = LoadImage(paths[dir][frame]);
      ImageResizeNN(&img, 64, 88);
      asset_manager.player_walk_white[dir][frame] = LoadTextureFromImage(img);
      SetTextureFilter(asset_manager.player_walk_white[dir][frame],
                       TEXTURE_FILTER_POINT);
      UnloadImage(img);
    }
  }
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

Texture2D *
asset_manager_get_player_walk_white_texture(EntityDirection direction,
                                            int frame) {
  return &asset_manager.player_walk_white[direction][frame];
}

Texture2D *asset_manager_get_player_death_texture(int frame) {
  return &asset_manager.player_death[frame];
}

void asset_manager_load_map_textures(MapType map_type) {
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
  asset_manager.map_tiles = malloc(sizeof(Texture2D) * size);

  char path[150];

  sprintf(path, "%s%s", map_path, image_path[0]);
  images[0] = LoadImage(path);
  ImageResizeNN(&images[0], 272 * 4, 208 * 4);
  asset_manager.map_background = LoadTextureFromImage(images[0]);

  for (int i = 1; i <= 3; i++) {
    sprintf(path, "%s%s", map_path, image_path[i]);
    images[i] = LoadImage(path);
    ImageResizeNN(&images[i], TILE_SIZE, TILE_SIZE);
    asset_manager.bomb[i - 1] = LoadTextureFromImage(images[i]);
  }

  for (int i = 4; i <= 9; i++) {
    sprintf(path, "%s%s", map_path, image_path[i]);
    images[i] = LoadImage(path);
    ImageResizeNN(&images[i], TILE_SIZE, TILE_SIZE);
    asset_manager.brick_destruction[i - 4] = LoadTextureFromImage(images[i]);
  }

  for (int i = 10; i < size; i++) {
    sprintf(path, "%s%s", map_path, image_path[i]);
    images[i] = LoadImage(path);
    ImageResizeNN(&images[i], TILE_SIZE, TILE_SIZE);
    asset_manager.map_tiles[i] = LoadTextureFromImage(images[i]);
  }

  for (int i = 0; i < size; i++) {
    SetTextureFilter(asset_manager.map_tiles[i], TEXTURE_FILTER_POINT);
    UnloadImage(images[i]);
  }

  asset_manager_load_explosion_textures(map_path);
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

void asset_manager_load_explosion_textures(char *map_path) {
  asset_manager_load_explosion_center_textures(map_path);
  asset_manager_load_explosion_middle_textures(map_path);
  asset_manager_load_explosion_final_textures(map_path);
}

void asset_manager_load_explosion_center_textures(char *map_path) {
  const char *paths[5] = {"EXPLOSION_CENTER_1.png", "EXPLOSION_CENTER_2.png",
                          "EXPLOSION_CENTER_3.png", "EXPLOSION_CENTER_4.png",
                          "EXPLOSION_CENTER_5.png"};

  char path[150];

  for (int frame = 0; frame < 5; frame++) {
    sprintf(path, "%s%s", map_path, paths[frame]);
    Image img = LoadImage(path);
    ImageResizeNN(&img, TILE_SIZE, TILE_SIZE);
    asset_manager.explosion_center[frame] = LoadTextureFromImage(img);
    SetTextureFilter(asset_manager.explosion_center[frame],
                     TEXTURE_FILTER_POINT);
    UnloadImage(img);
  }
}
void asset_manager_load_explosion_middle_textures(char *map_path) {
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
      asset_manager.explosion_middle[dir][frame] = LoadTextureFromImage(img);
      SetTextureFilter(asset_manager.explosion_middle[dir][frame],
                       TEXTURE_FILTER_POINT);
      UnloadImage(img);
    }
  }
}

void asset_manager_load_explosion_final_textures(char *map_path) {
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

void asset_manager_load_hud_textures() {
  asset_manager.hud_top = LoadTexture("assets/hud/TOP_HUD.png");
}

Texture2D *asset_manager_get_hud_texture() { return &asset_manager.hud_top; }
