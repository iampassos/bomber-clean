#ifndef ASSETS_MAPS_H
#define ASSETS_MAPS_H

#include "core/map.h"
#include <raylib.h>

typedef struct {
  Texture2D background;
  Texture2D *tiles;

  Texture2D brick_destruction[6];
  Texture2D bomb[3];
} AssetsMaps;

void assets_maps_load_textures(MapType map_type);
Texture2D *assets_maps_get_background_texture();
Texture2D *assets_maps_get_tiles_textures();

Texture2D *assets_maps_get_bomb_texture(int frame);
Texture2D *assets_maps_get_brick_destruction_texture(int frame);

#endif
