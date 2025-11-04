#include "assets_players.h"
#include "asset_manager.h"
#include <stdio.h>

void assets_players_load_player_textures() {
  assets_players_load_player_walk_textures();
  assets_players_load_player_walk_white_textures();
  assets_players_load_player_death_textures();
}

void assets_players_load_player_walk_white_textures() {
  char *player_path = "assets/sprites/player/";

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
      ImageResizeNN(&img, 64, 88);
      asset_manager.assets_players.player_walk_white[dir][frame] =
          LoadTextureFromImage(img);
      SetTextureFilter(
          asset_manager.assets_players.player_walk_white[dir][frame],
          TEXTURE_FILTER_POINT);
      UnloadImage(img);
    }
  }
}

void assets_players_load_player_walk_textures() {
  char *player_path = "assets/sprites/player/";

  const char *paths[4][3] = {{"UP1.png", "UP2.png", "UP3.png"},
                             {"DOWN1.png", "DOWN2.png", "DOWN3.png"},
                             {"LEFT1.png", "LEFT2.png", "LEFT3.png"},
                             {"RIGHT1.png", "RIGHT2.png", "RIGHT3.png"}};

  char path[100];

  for (int dir = 0; dir < 4; dir++) {
    for (int frame = 0; frame < 3; frame++) {
      sprintf(path, "%s%s", player_path, paths[dir][frame]);
      Image img = LoadImage(path);
      ImageResizeNN(&img, 64, 88);
      asset_manager.assets_players.player_walk[dir][frame] =
          LoadTextureFromImage(img);
      SetTextureFilter(asset_manager.assets_players.player_walk[dir][frame],
                       TEXTURE_FILTER_POINT);
      UnloadImage(img);
    }
  }
}

void assets_players_load_player_death_textures() {
  char *player_path = "assets/sprites/player/";

  const char *paths[7] = {
      "PLAYER_DEATH_1.png", "PLAYER_DEATH_2.png", "PLAYER_DEATH_3.png",
      "PLAYER_DEATH_4.png", "PLAYER_DEATH_5.png", "PLAYER_DEATH_6.png",
      "PLAYER_DEATH_7.png",
  };

  char path[100];

  for (int frame = 0; frame < 7; frame++) {
    sprintf(path, "%s%s", player_path, paths[frame]);
    Image img = LoadImage(path);
    ImageResizeNN(&img, 64, 88);
    asset_manager.assets_players.player_death[frame] =
        LoadTextureFromImage(img);
    SetTextureFilter(asset_manager.assets_players.player_death[frame],
                     TEXTURE_FILTER_POINT);
    UnloadImage(img);
  }
}

Texture2D *assets_players_get_player_walk_texture(EntityDirection direction,
                                                  int frame) {
  return &asset_manager.assets_players.player_walk[direction][frame];
}

Texture2D *
assets_players_get_player_walk_white_texture(EntityDirection direction,
                                             int frame) {
  return &asset_manager.assets_players.player_walk_white[direction][frame];
}

Texture2D *assets_players_get_player_death_texture(int frame) {
  return &asset_manager.assets_players.player_death[frame];
}
