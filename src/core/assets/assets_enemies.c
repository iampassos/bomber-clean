#include "assets_enemies.h"
#include "asset_manager.h"
#include <raylib.h>
#include <stdio.h>

void assets_enemies_load_ballom_textures() {
  char *ballom_path = "assets/sprites/enemies/ballom/";

  const char *paths[4][4] = {{"UP1", "UP2", "UP3", "UP4"},
                             {"DOWN1", "DOWN2", "DOWN3", "DOWN4"},
                             {"LEFT1", "LEFT2", "LEFT3", "LEFT4"},
                             {"RIGHT1", "RIGHT2", "RIGHT3", "RIGHT4"}};

  char path[100];

  for (int dir = 0; dir < 4; dir++) {
    for (int frame = 0; frame < 4; frame++) {
      sprintf(path, "%s%s_WHITE.png", ballom_path, paths[dir][frame]);
      Image img = LoadImage(path);
      ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
      ImageResizeNN(&img, 64, 88);
      ImageColorReplace(&img, (Color){48, 136, 160, 255}, BLANK);
      asset_manager.assets_enemies.ballom_white[dir][frame] =
          LoadTextureFromImage(img);
      SetTextureFilter(asset_manager.assets_enemies.ballom_white[dir][frame],
                       TEXTURE_FILTER_POINT);
      UnloadImage(img);
    }
  }

  for (int dir = 0; dir < 4; dir++) {
    for (int frame = 0; frame < 4; frame++) {
      sprintf(path, "%s%s.png", ballom_path, paths[dir][frame]);
      Image img = LoadImage(path);
      ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
      ImageResizeNN(&img, 64, 88);
      ImageColorReplace(&img, (Color){48, 136, 160, 255}, BLANK);
      asset_manager.assets_enemies.ballom[dir][frame] =
          LoadTextureFromImage(img);
      SetTextureFilter(asset_manager.assets_enemies.ballom_white[dir][frame],
                       TEXTURE_FILTER_POINT);
      UnloadImage(img);
    }
  }
}

Texture2D *assets_enemies_get_normal_ballom_texture(EntityDirection direction,
                                                    int frame) {
  return &asset_manager.assets_enemies.ballom[direction][frame];
}

Texture2D *assets_enemies_get_white_ballom_texture(EntityDirection direction,
                                                   int frame) {
  return &asset_manager.assets_enemies.ballom_white[direction][frame];
}
