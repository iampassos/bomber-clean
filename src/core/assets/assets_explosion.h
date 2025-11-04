#ifndef ASSETS_EXPLOSION_H
#define ASSETS_EXPLOSION_H

#include "entities/entity.h"
#include <raylib.h>

typedef struct {
  Texture2D center[5];
  Texture2D middle[2][5];
  Texture2D final[4][5];
} AssetsExplosion;

void assets_explosion_load_textures();
void assets_explosion_load_center_textures();
void assets_explosion_load_middle_textures();
void assets_explosion_load_final_textures();

Texture2D *assets_explosion_get_center_texture(int frame);
Texture2D *assets_explosion_get_middle_texture(EntityDirection direction,
                                               int frame);
Texture2D *assets_explosion_get_final_texture(EntityDirection direction,
                                              int frame);

#endif
