#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "core/map.h"
#include "entities/entity.h"
#include "entities/power_up.h"

#include <raylib.h>

typedef struct {
  Texture2D player_walk[4][3];
  Texture2D player_death[7];
  Texture2D bomb[3];
  Texture2D brick_destruction[6];

  Texture2D power_ups[3];

  Texture2D map_background;
  Texture2D *map_tiles;

  Texture2D hud_top;
} AssetManager;

extern AssetManager asset_manager;

void asset_manager_init();
void asset_manager_load_all();

void asset_manager_load_power_ups_textures();
Texture2D *asset_manager_get_power_up_texture(PowerUpType type);

void asset_manager_load_player_textures();
void asset_manager_load_player_walk_textures();
void asset_manager_load_player_death_textures();
Texture2D *asset_manager_get_player_walk_texture(EntityDirection direction,
                                                 int frame);
Texture2D *asset_manager_get_player_death_texture(int frame);

void asset_manager_load_map_textures(MapType map_type);
Texture2D *asset_manager_get_map_background_texture();
Texture2D *asset_manager_get_map_tiles_textures();

Texture2D *asset_manager_get_bomb_texture(int frame);
Texture2D *asset_manager_get_brick_destruction_texture(int frame);
Texture2D *asset_manager_get_explosion_texture(int frame);

void asset_manager_load_hud_textures();
Texture2D *asset_manager_get_hud_texture();

#endif
