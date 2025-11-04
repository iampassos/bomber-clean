#ifndef ASSETS_PLAYERS_H
#define ASSETS_PLAYERS_H

#include "entities/entity.h"
#include <raylib.h>

typedef struct {
  Texture2D player_walk[4][3];
  Texture2D player_walk_white[4][3];
  Texture2D player_death[7];
} AssetsPlayers;

void assets_players_load_player_textures();
void assets_players_load_player_walk_textures();
void assets_players_load_player_walk_white_textures();
void assets_players_load_player_death_textures();
Texture2D *assets_players_get_player_walk_texture(EntityDirection direction,
                                                  int frame);
Texture2D *
assets_players_get_player_walk_white_texture(EntityDirection direction,
                                             int frame);
Texture2D *assets_players_get_player_death_texture(int frame);

#endif
