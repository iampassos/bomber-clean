#include "assets_players.h"
#include "asset_manager.h"

void assets_players_load_player_textures() {
  assets_players_load_player_walk_textures();
  assets_players_load_player_walk_white_textures();
  assets_players_load_player_death_textures();
}

void assets_players_load_player_walk_white_textures() {
  const char *paths[4][3] = {{"assets/sprites/player/UP1_WHITE.png",
                              "assets/sprites/player/UP2_WHITE.png",
                              "assets/sprites/player/UP3_WHITE.png"},
                             {"assets/sprites/player/DOWN1_WHITE.png",
                              "assets/sprites/player/DOWN2_WHITE.png",
                              "assets/sprites/player/DOWN3_WHITE.png"},
                             {"assets/sprites/player/LEFT1_WHITE.png",
                              "assets/sprites/player/LEFT2_WHITE.png",
                              "assets/sprites/player/LEFT3_WHITE.png"},
                             {"assets/sprites/player/RIGHT1_WHITE.png",
                              "assets/sprites/player/RIGHT2_WHITE.png",
                              "assets/sprites/player/RIGHT3_WHITE.png"}};

  for (int dir = 0; dir < 4; dir++) {
    for (int frame = 0; frame < 3; frame++) {
      Image img = LoadImage(paths[dir][frame]);
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
  const char *paths[4][3] = {
      {"assets/sprites/player/UP1.png", "assets/sprites/player/UP2.png",
       "assets/sprites/player/UP3.png"},
      {"assets/sprites/player/DOWN1.png", "assets/sprites/player/DOWN2.png",
       "assets/sprites/player/DOWN3.png"},
      {"assets/sprites/player/LEFT1.png", "assets/sprites/player/LEFT2.png",
       "assets/sprites/player/LEFT3.png"},
      {"assets/sprites/player/RIGHT1.png", "assets/sprites/player/RIGHT2.png",
       "assets/sprites/player/RIGHT3.png"}};

  for (int dir = 0; dir < 4; dir++) {
    for (int frame = 0; frame < 3; frame++) {
      Image img = LoadImage(paths[dir][frame]);
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
  const char *paths[7] = {
      "assets/sprites/player/PLAYER_DEATH_1.png",
      "assets/sprites/player/PLAYER_DEATH_2.png",
      "assets/sprites/player/PLAYER_DEATH_3.png",
      "assets/sprites/player/PLAYER_DEATH_4.png",
      "assets/sprites/player/PLAYER_DEATH_5.png",
      "assets/sprites/player/PLAYER_DEATH_6.png",
      "assets/sprites/player/PLAYER_DEATH_7.png",
  };

  for (int frame = 0; frame < 7; frame++) {
    Image img = LoadImage(paths[frame]);
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
