#ifndef ASSETS_MAPS_H
#define ASSETS_MAPS_H

#include "core/map.h"
#include "entities/entity.h"
#include <raylib.h>

typedef struct {
  Texture2D map_background;
  Texture2D *map_tiles;

  Texture2D brick_destruction[6];
  Texture2D bomb[3];
  Texture2D explosion_center[5];
  Texture2D explosion_middle[2][5];
  Texture2D explosion_final[4][5];
} AssetsMaps;

void assets_maps_load_map_textures(MapType map_type);
Texture2D *assets_maps_get_map_background_texture();
Texture2D *assets_maps_get_map_tiles_textures();

Texture2D *assets_maps_get_bomb_texture(int frame);
Texture2D *assets_maps_get_brick_destruction_texture(int frame);

void assets_maps_load_explosion_textures(char *map_path);
void assets_maps_load_explosion_center_textures(char *map_path);
void assets_maps_load_explosion_middle_textures(char *map_path);
void assets_maps_load_explosion_final_textures(char *map_path);

Texture2D *assets_maps_get_explosion_center_texture(int frame);
Texture2D *assets_maps_get_explosion_middle_texture(EntityDirection direction,
                                                    int frame);
Texture2D *assets_maps_get_explosion_final_texture(EntityDirection direction,
                                                   int frame);

#endif
