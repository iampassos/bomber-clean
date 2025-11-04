#ifndef ASSETS_ENEMIES_H
#define ASSETS_ENEMIES_H

#include "entities/entity.h"
#include <raylib.h>

typedef struct {
  Texture2D ballom[4][4];
} AssetsEnemies;

void assets_enemies_load_enemy_textures();

#endif
