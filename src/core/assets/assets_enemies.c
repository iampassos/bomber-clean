#include "assets_enemies.h"
#include "asset_manager.h"
#include <stdio.h>

void assets_enemies_load_ballom_textures() {
  char *ballom_path = "assets/sprites/enemies/ballom/";

  const char *paths[4][4] = {
      {"UP1.png", "UP2.png", "UP3.png", "UP4.png"},
      {"DOWN1.png", "DOWN2.png", "DOWN3.png", "DOWN4.png"},
      {"LEFT1.png", "LEFT2.png", "LEFT3.png", "LEFT4.png"},
      {"RIGHT1.png", "RIGHT2.png", "RIGHT3.png", "RIGHT4.png"}};

  char path[100];

  for (int dir = 0; dir < 4; dir++) {
    for (int frame = 0; frame < 4; frame++) {
      sprintf(path, "%s%s", ballom_path, paths[dir][frame]);
      Image img = LoadImage(path);
      ImageResizeNN(&img, 64, 88);
      asset_manager.assets_enemies.ballom[dir][frame] =
          LoadTextureFromImage(img);
      SetTextureFilter(asset_manager.assets_enemies.ballom[dir][frame],
                       TEXTURE_FILTER_POINT);
      UnloadImage(img);
    }
  }
}

Texture2D *assets_enemies_get_ballom_texture(EntityDirection direction,
                                             int frame) {
  return &asset_manager.assets_enemies.ballom[direction][frame];
}
