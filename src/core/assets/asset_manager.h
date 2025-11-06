#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "core/assets/assets_enemies.h"
#include "core/assets/assets_explosion.h"
#include "core/assets/assets_maps.h"
#include "core/assets/assets_players.h"
#include "entities/power_up.h"

#include <raylib.h>

typedef struct {
  Texture2D power_ups[6][2];
  Texture2D hud_top;

  Font fonts[1];

  AssetsMaps assets_maps;
  AssetsPlayers assets_players;
  AssetsEnemies assets_enemies;
  AssetsExplosion assets_explosion;
} AssetManager;

extern AssetManager asset_manager;

void asset_manager_init();
void asset_manager_load_all();

void asset_manager_load_power_ups_textures();
Texture2D *asset_manager_get_power_up_texture(PowerUpType type, int frame);

void asset_manager_load_fonts();
Font *asset_manager_get_font(int i);

void asset_manager_load_hud_textures();
Texture2D *asset_manager_get_hud_texture();

#endif
