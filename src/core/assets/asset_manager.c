#include "asset_manager.h"
#include "core/assets/assets_explosion.h"
#include "core/common.h"
#include <raylib.h>
#include <stdio.h>

AssetManager asset_manager = {0};

void asset_manager_init() {}

void asset_manager_load_all() {
  assets_players_load_textures();
  assets_explosion_load_textures();
  asset_manager_load_hud_textures();
  asset_manager_load_power_ups_textures();
}

void asset_manager_load_power_ups_textures() {
  char *power_up_path = "assets/sprites/power_ups/";

  const char *paths[6][2] = {
      {
          "LIFE_1",
          "LIFE_2",
      },
      {
          "SPEED_UP_1",
          "SPEED_UP_2",
      },
      {
          "BOMB_1",
          "BOMB_2",
      },
      {
          "RADIUS_1",
          "RADIUS_2",
      },
      {
          "MAXIMUM_RADIUS_1",
          "MAXIMUM_RADIUS_2",
      },
      {
          "INVENCIBLE_1",
          "INVENCIBLE_2",
      },
  };

  char path[100];

  for (int power_up = 0; power_up < 6; power_up++) {
    for (int frame = 0; frame < 2; frame++) {
      sprintf(path, "%s%s.png", power_up_path, paths[power_up][frame]);
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

void asset_manager_load_hud_textures() {
  asset_manager.hud_top = LoadTexture("assets/hud/TOP_HUD.png");
}

Texture2D *asset_manager_get_hud_texture() { return &asset_manager.hud_top; }
