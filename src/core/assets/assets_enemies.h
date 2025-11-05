#ifndef ASSETS_ENEMIES_H
#define ASSETS_ENEMIES_H

#include "entities/entity.h"
#include <raylib.h>

typedef struct {
  Texture2D ballom[4][4];
  Texture2D ballom_white[4][4];
} AssetsEnemies;

void assets_enemies_load_ballom_textures();
Texture2D *assets_enemies_get_normal_ballom_texture(EntityDirection direction,
                                                    int frame);
Texture2D *assets_enemies_get_white_ballom_texture(EntityDirection direction,
                                                   int frame);

#endif
