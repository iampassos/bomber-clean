#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "core/map.h"
#include "entities/player.h"

#include <raylib.h>

typedef struct {
  Texture2D player[4][3];
  Texture2D bomb[3];

  Texture2D map_background;
  Texture2D *map_tiles;

  Texture2D hud_top;
} AssetManager;

extern AssetManager asset_manager;

void asset_manager_init();
void asset_manager_load_all();

void asset_manager_load_player_textures();
Texture2D *asset_manager_get_player_texture(Direction direction, int frame);

void asset_manager_load_map_textures(MapType map_type);
Texture2D *asset_manager_get_map_background_texture();
Texture2D *asset_manager_get_map_tiles_textures();

Texture2D *asset_manager_get_bomb_texture(int frame);
Texture2D *asset_manager_get_explosion_texture(int frame);

void asset_manager_load_hud_textures();
Texture2D *asset_manager_get_hud_texture();

#endif
