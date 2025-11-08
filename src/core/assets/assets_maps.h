#ifndef ASSETS_MAPS_H
#define ASSETS_MAPS_H

#include "core/map.h"
#include <raylib.h>

typedef struct {
  Texture2D *tiles;
  int tile_count;
  Texture2D background;
  Texture2D brick_destruction[6];
  Texture2D bomb[3];
  Texture2D bomb_machine[3];
  Texture2D power_up_explosion[7];
} AssetsMaps;

void assets_maps_load_textures(MapType map_type);
void assets_maps_unload_all();

void assets_maps_load_jump_zone();
void assets_maps_load_duel_zone();
void assets_maps_load_light_zone();
void assets_maps_load_speed_zone();
void assets_maps_load_western_zone();
void assets_maps_load_belt_zone();
void assets_maps_load_normal_zone();
void assets_maps_load_bomb_zone();

Texture2D *assets_maps_get_background_texture();
Texture2D *assets_maps_get_tiles_textures();

Texture2D *assets_maps_get_bomb_texture(int frame);
Texture2D *assets_maps_get_bomb_machine_texture(int frame);
Texture2D *assets_maps_get_brick_destruction_texture(int frame);
Texture2D *assets_maps_get_power_up_explosion_texture(int frame);

#endif
