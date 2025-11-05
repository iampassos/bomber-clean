#include "assets_players.h"
#include "asset_manager.h"
#include <stdio.h>

void assets_players_load_textures() {
  assets_players_load_walk_textures();
  assets_players_load_walk_white_textures();
  assets_players_load_death_textures();
}

void assets_players_load_walk_white_textures() {
  char *player_path = "assets/sprites/players/player1/";

  const char *paths[4][3] = {
      {"UP1_WHITE.png", "UP2_WHITE.png", "UP3_WHITE.png"},
      {"DOWN1_WHITE.png", "DOWN2_WHITE.png", "DOWN3_WHITE.png"},
      {"LEFT1_WHITE.png", "LEFT2_WHITE.png", "LEFT3_WHITE.png"},
      {"RIGHT1_WHITE.png", "RIGHT2_WHITE.png", "RIGHT3_WHITE.png"}};

  char path[100];

  for (int dir = 0; dir < 4; dir++) {
    for (int frame = 0; frame < 3; frame++) {
      sprintf(path, "%s%s", player_path, paths[dir][frame]);
      Image img = LoadImage(path);
      ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
      ImageResizeNN(&img, 64, 88);
      ImageColorReplace(&img, (Color){48, 136, 160, 255}, BLANK);
      asset_manager.assets_players.white[dir][frame] =
          LoadTextureFromImage(img);
      SetTextureFilter(asset_manager.assets_players.white[dir][frame],
                       TEXTURE_FILTER_POINT);
      UnloadImage(img);
    }
  }
}

void assets_players_load_walk_textures() {
  char *player_path = "assets/sprites/players/player1/";

  const char *paths[4][3] = {{"UP1.png", "UP2.png", "UP3.png"},
                             {"DOWN1.png", "DOWN2.png", "DOWN3.png"},
                             {"LEFT1.png", "LEFT2.png", "LEFT3.png"},
                             {"RIGHT1.png", "RIGHT2.png", "RIGHT3.png"}};

  char path[100];

  for (int dir = 0; dir < 4; dir++) {
    for (int frame = 0; frame < 3; frame++) {
      sprintf(path, "%s%s", player_path, paths[dir][frame]);
      Image img = LoadImage(path);
      ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
      ImageResizeNN(&img, 64, 88);
      ImageColorReplace(&img, (Color){48, 136, 160, 255}, BLANK);
      asset_manager.assets_players.walk[dir][frame] = LoadTextureFromImage(img);
      SetTextureFilter(asset_manager.assets_players.walk[dir][frame],
                       TEXTURE_FILTER_POINT);
      UnloadImage(img);
    }
  }
}

void assets_players_load_death_textures() {
  char *player_path = "assets/sprites/players/player1/";

  const char *paths[7] = {
      "DEATH1.png", "DEATH2.png", "DEATH3.png", "DEATH4.png",
      "DEATH5.png", "DEATH6.png", "DEATH7.png",
  };

  char path[100];

  for (int frame = 0; frame < 7; frame++) {
    sprintf(path, "%s%s", player_path, paths[frame]);
    Image img = LoadImage(path);
    ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    ImageResizeNN(&img, 64, 88);
    ImageColorReplace(&img, (Color){48, 136, 160, 255}, BLANK);
    asset_manager.assets_players.death[frame] = LoadTextureFromImage(img);
    SetTextureFilter(asset_manager.assets_players.death[frame],
                     TEXTURE_FILTER_POINT);
    UnloadImage(img);
  }
}

Texture2D *assets_players_get_walk_texture(EntityDirection direction,
                                           int frame) {
  return &asset_manager.assets_players.walk[direction][frame];
}

Texture2D *assets_players_get_walk_white_texture(EntityDirection direction,
                                                 int frame) {
  return &asset_manager.assets_players.white[direction][frame];
}

Texture2D *assets_players_get_death_texture(int frame) {
  return &asset_manager.assets_players.death[frame];
}
