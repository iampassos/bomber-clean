#include "asset_manager.h"
#include "core/assets/assets_enemies.h"
#include "core/assets/assets_explosion.h"
#include "core/assets/assets_maps.h"
#include "core/assets/assets_players.h"
#include "core/assets/assets_sounds.h"
#include "core/common.h"
#include <raylib.h>
#include <stdio.h>

AssetManager asset_manager = {0};

void asset_manager_init() {
  asset_manager_load_fonts();
  assets_sounds_load_sounds();
}

void asset_manager_load_menu() { asset_manager_load_menu_textures(); }

void asset_manager_load_game() {
  assets_players_load_textures();
  assets_explosion_load_textures();
  asset_manager_load_hud_textures();
  asset_manager_load_fullscreen_textures();
  asset_manager_load_power_ups_textures();
}

void asset_manager_unload_all() {
  asset_manager_unload_game();
  asset_manager_unload_menu();
  assets_sounds_unload_all();

  for (int i = 0; i < 1; i++)
    UnloadFont(asset_manager.fonts[i]);
}

void asset_manager_unload_game() {
  assets_enemies_unload_all();
  assets_explosion_unload_all();
  assets_maps_unload_all();
  assets_players_unload_all();

  UnloadTexture(asset_manager.hud_top);
  UnloadTexture(asset_manager.fullscreen_background);

  for (int i = 0; i < 6; i++)
    for (int j = 0; j < 2; j++)
      UnloadTexture(asset_manager.power_ups[i][j]);
}

void asset_manager_unload_menu() {
  UnloadTexture(asset_manager.menu_background);
  UnloadTexture(asset_manager.menu_background_2);
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

void asset_manager_load_fonts() {
  asset_manager.fonts[0] = LoadFont("assets/fonts/PressStart2P-Regular.ttf");
}

Font *asset_manager_get_font(int i) { return &asset_manager.fonts[i]; }

Texture2D *asset_manager_get_power_up_texture(PowerUpType type, int frame) {
  return &asset_manager.power_ups[type][frame];
}

void asset_manager_load_hud_textures() {
  asset_manager.hud_top = LoadTexture("assets/hud/TOP_HUD.png");
}

Texture2D *asset_manager_get_hud_texture() { return &asset_manager.hud_top; }

void asset_manager_load_fullscreen_textures() {
  asset_manager.fullscreen_background =
      LoadTexture("assets/hud/FULLSCREEN_BACKGROUND.png");
}
Texture2D *asset_manager_get_fullscreen_texture() {
  return &asset_manager.fullscreen_background;
}

void asset_manager_load_menu_textures() {
  asset_manager.menu_background = LoadTexture("assets/MENU.png");
  asset_manager.menu_background_2 = LoadTexture("assets/MENU_2.png");
  asset_manager.menu_leaderboard = LoadTexture("assets/LEADERBOARD_FULL.png");
  asset_manager.menu_leaderboard_2 =
      LoadTexture("assets/LEADERBOARD_SMALL.png");
}

Texture2D *asset_manager_get_menu_background() {
  return &asset_manager.menu_background;
}

Texture2D *asset_manager_get_menu_background_small() {
  return &asset_manager.menu_background_2;
}

Texture2D *asset_manager_get_menu_leaderboard() {
  return &asset_manager.menu_leaderboard;
}

Texture2D *asset_manager_get_menu_leaderboard_small() {
  return &asset_manager.menu_leaderboard_2;
}
