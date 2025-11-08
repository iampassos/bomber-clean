#include "assets_players.h"
#include "asset_manager.h"
#include <raylib.h>
#include <stdio.h>

void assets_players_load_textures() {
  assets_players_load_walk_white_textures();
}

void assets_players_load_player_textures(int player_id) {
  assets_players_load_walk_textures(player_id);
  assets_players_load_death_textures(player_id);
}

void assets_players_unload_all() {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      for (int k = 0; k < 3; k++)
        UnloadTexture(asset_manager.assets_players.walk[i][j][k]);

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 3; j++)
      UnloadTexture(asset_manager.assets_players.white[i][j]);

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 7; j++)
      UnloadTexture(asset_manager.assets_players.death[i][j]);
}

void assets_players_load_walk_white_textures() {
  char *player_path = "assets/sprites/players/";

  const char *paths[4][3] = {{"UP1", "UP2", "UP3"},
                             {"DOWN1", "DOWN2", "DOWN3"},
                             {"LEFT1", "LEFT2", "LEFT3"},
                             {"RIGHT1", "RIGHT2", "RIGHT3"}};

  char path[100];

  for (int dir = 0; dir < 4; dir++) {
    for (int frame = 0; frame < 3; frame++) {
      sprintf(path, "%s%s_WHITE.png", player_path, paths[dir][frame]);
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

void assets_players_load_walk_textures(int player_id) {
  char player_path[50];
  sprintf(player_path, "assets/sprites/players/player%d/", player_id);

  const char *paths[4][3] = {{"UP1", "UP2", "UP3"},
                             {"DOWN1", "DOWN2", "DOWN3"},
                             {"LEFT1", "LEFT2", "LEFT3"},
                             {"RIGHT1", "RIGHT2", "RIGHT3"}};

  char path[100];

  for (int dir = 0; dir < 4; dir++) {
    for (int frame = 0; frame < 3; frame++) {
      sprintf(path, "%s%s.png", player_path, paths[dir][frame]);
      Image img = LoadImage(path);
      ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
      ImageResizeNN(&img, 64, 88);
      ImageColorReplace(&img, (Color){48, 136, 160, 255}, BLANK);
      asset_manager.assets_players.walk[player_id][dir][frame] =
          LoadTextureFromImage(img);
      SetTextureFilter(asset_manager.assets_players.walk[player_id][dir][frame],
                       TEXTURE_FILTER_POINT);
      UnloadImage(img);
    }
  }
}

void assets_players_load_death_textures(int player_id) {
  char player_path[50];
  sprintf(player_path, "assets/sprites/players/player%d/", player_id);

  const char *paths[7] = {
      "DEATH1", "DEATH2", "DEATH3", "DEATH4", "DEATH5", "DEATH6", "DEATH7",
  };

  char path[100];

  for (int frame = 0; frame < 7; frame++) {
    sprintf(path, "%s%s.png", player_path, paths[frame]);
    Image img = LoadImage(path);
    ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    ImageResizeNN(&img, 64, 88);
    ImageColorReplace(&img, (Color){48, 136, 160, 255}, BLANK);
    asset_manager.assets_players.death[player_id][frame] =
        LoadTextureFromImage(img);
    SetTextureFilter(asset_manager.assets_players.death[player_id][frame],
                     TEXTURE_FILTER_POINT);
    UnloadImage(img);
  }
}

Texture2D *assets_players_get_walk_texture(int player_id,
                                           EntityDirection direction,
                                           int frame) {
  return &asset_manager.assets_players.walk[player_id][direction][frame];
}

Texture2D *assets_players_get_walk_white_texture(EntityDirection direction,
                                                 int frame) {
  return &asset_manager.assets_players.white[direction][frame];
}

Texture2D *assets_players_get_death_texture(int player_id, int frame) {
  return &asset_manager.assets_players.death[player_id][frame];
}
