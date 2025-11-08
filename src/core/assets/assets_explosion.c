#include "assets_explosion.h"
#include "asset_manager.h"
#include "core/common.h"
#include <raylib.h>
#include <stdio.h>

void assets_explosion_load_textures() {
  assets_explosion_load_center_textures();
  assets_explosion_load_middle_textures();
  assets_explosion_load_final_textures();
}

void assets_explosion_unload_all(void) {
  for (int i = 0; i < 5; i++) {
    UnloadTexture(asset_manager.assets_explosion.center[i]);

    for (int j = 0; j < 2; j++)
      UnloadTexture(asset_manager.assets_explosion.middle[j][i]);

    for (int j = 0; j < 4; j++)
      UnloadTexture(asset_manager.assets_explosion.final[j][i]);
  }
}

void assets_explosion_load_center_textures() {
  char *explosion_path = "assets/sprites/explosion/";

  const char *paths[5] = {"EXPLOSION_CENTER_1", "EXPLOSION_CENTER_2",
                          "EXPLOSION_CENTER_3", "EXPLOSION_CENTER_4",
                          "EXPLOSION_CENTER_5"};

  char path[150];

  for (int frame = 0; frame < 5; frame++) {
    sprintf(path, "%s%s.png", explosion_path, paths[frame]);
    Image img = LoadImage(path);
    ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    ImageResizeNN(&img, TILE_SIZE, TILE_SIZE);
    ImageColorReplace(&img, (Color){48, 136, 160, 255}, BLANK);
    asset_manager.assets_explosion.center[frame] = LoadTextureFromImage(img);
    SetTextureFilter(asset_manager.assets_explosion.center[frame],
                     TEXTURE_FILTER_POINT);
    UnloadImage(img);
  }
}
void assets_explosion_load_middle_textures() {
  char *explosion_path = "assets/sprites/explosion/";

  const char *paths[2][5] = {
      {"EXPLOSION_MIDDLE_VERTICAL_1", "EXPLOSION_MIDDLE_VERTICAL_2",
       "EXPLOSION_MIDDLE_VERTICAL_3", "EXPLOSION_MIDDLE_VERTICAL_4",
       "EXPLOSION_MIDDLE_VERTICAL_5"},
      {"EXPLOSION_MIDDLE_HORIZONTAL_1", "EXPLOSION_MIDDLE_HORIZONTAL_2",
       "EXPLOSION_MIDDLE_HORIZONTAL_3", "EXPLOSION_MIDDLE_HORIZONTAL_4",
       "EXPLOSION_MIDDLE_HORIZONTAL_5"},
  };

  char path[150];

  for (int dir = 0; dir < 2; dir++) {
    for (int frame = 0; frame < 5; frame++) {
      sprintf(path, "%s%s.png", explosion_path, paths[dir][frame]);
      Image img = LoadImage(path);
      ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
      ImageResizeNN(&img, TILE_SIZE, TILE_SIZE);
      ImageColorReplace(&img, (Color){48, 136, 160, 255}, BLANK);
      asset_manager.assets_explosion.middle[dir][frame] =
          LoadTextureFromImage(img);
      SetTextureFilter(asset_manager.assets_explosion.middle[dir][frame],
                       TEXTURE_FILTER_POINT);
      UnloadImage(img);
    }
  }
}

void assets_explosion_load_final_textures() {
  char *explosion_path = "assets/sprites/explosion/";

  const char *paths[4][5] = {
      {"EXPLOSION_TOP_1.png", "EXPLOSION_TOP_2.png", "EXPLOSION_TOP_3.png",
       "EXPLOSION_TOP_4.png", "EXPLOSION_TOP_5.png"},
      {"EXPLOSION_BOTTOM_1.png", "EXPLOSION_BOTTOM_2.png",
       "EXPLOSION_BOTTOM_3.png", "EXPLOSION_BOTTOM_4.png",
       "EXPLOSION_BOTTOM_5.png"},
      {"EXPLOSION_LEFT_1.png", "EXPLOSION_LEFT_2.png", "EXPLOSION_LEFT_3.png",
       "EXPLOSION_LEFT_4.png", "EXPLOSION_LEFT_5.png"},
      {"EXPLOSION_RIGHT_1.png", "EXPLOSION_RIGHT_2.png",
       "EXPLOSION_RIGHT_3.png", "EXPLOSION_RIGHT_4.png",
       "EXPLOSION_RIGHT_5.png"},

  };

  char path[150];

  for (int dir = 0; dir < 4; dir++) {
    for (int frame = 0; frame < 5; frame++) {
      sprintf(path, "%s%s", explosion_path, paths[dir][frame]);
      Image img = LoadImage(path);
      ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
      ImageResizeNN(&img, TILE_SIZE, TILE_SIZE);
      ImageColorReplace(&img, (Color){48, 136, 160, 255}, BLANK);
      asset_manager.assets_explosion.final[dir][frame] =
          LoadTextureFromImage(img);
      SetTextureFilter(asset_manager.assets_explosion.final[dir][frame],
                       TEXTURE_FILTER_POINT);
      UnloadImage(img);
    }
  }
}

Texture2D *assets_explosion_get_center_texture(int frame) {
  return &asset_manager.assets_explosion.center[frame];
}

Texture2D *assets_explosion_get_middle_texture(EntityDirection direction,
                                               int frame) {
  return &asset_manager.assets_explosion
              .middle[direction == DIR_UP || direction == DIR_DOWN ? 0 : 1]
                     [frame];
}

Texture2D *assets_explosion_get_final_texture(EntityDirection direction,
                                              int frame) {
  return &asset_manager.assets_explosion.final[direction][frame];
}
