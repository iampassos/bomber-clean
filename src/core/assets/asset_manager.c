#include "asset_manager.h"
#include "core/common.h"
#include <raylib.h>
#include <stdio.h>

AssetManager asset_manager = {0};

void asset_manager_init() {}

void asset_manager_load_all() {
  assets_players_load_player_textures();
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

void asset_manager_load_hud_textures() {
  asset_manager.hud_top = LoadTexture("assets/hud/TOP_HUD.png");
}

Texture2D *asset_manager_get_hud_texture() { return &asset_manager.hud_top; }
