#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "core/assets/assets_enemies.h"
#include "core/assets/assets_explosion.h"
#include "core/assets/assets_maps.h"
#include "core/assets/assets_players.h"
#include "core/assets/assets_sounds.h"
#include "entities/power_up.h"

#include <raylib.h>

typedef struct {
  // All
  Font fonts[1];
  AssetsSounds assets_sounds;

  // Game
  Texture2D power_ups[6][2];
  Texture2D hud_top;
  Texture2D fullscreen_background;
  AssetsMaps assets_maps;
  AssetsPlayers assets_players;
  AssetsEnemies assets_enemies;
  AssetsExplosion assets_explosion;

  // Menu
  Texture2D menu_background;
  Texture2D menu_background_2;
} AssetManager;

extern AssetManager asset_manager;

void asset_manager_init();
void asset_manager_load_menu();
void asset_manager_load_game();

void asset_manager_unload_all();
void asset_manager_unload_game();
void asset_manager_unload_menu();

void asset_manager_load_power_ups_textures();
Texture2D *asset_manager_get_power_up_texture(PowerUpType type, int frame);

void asset_manager_load_fonts();
Font *asset_manager_get_font(int i);

void asset_manager_load_hud_textures();
Texture2D *asset_manager_get_hud_texture();

void asset_manager_load_fullscreen_textures();
Texture2D *asset_manager_get_fullscreen_texture();

void asset_manager_load_menu_textures();
Texture2D *asset_manager_get_menu_background();
Texture2D *asset_manager_get_menu_background_small();

#endif
