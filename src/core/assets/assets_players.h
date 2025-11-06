#ifndef ASSETS_PLAYERS_H
#define ASSETS_PLAYERS_H

#include "entities/entity.h"
#include <raylib.h>

typedef struct {
  Texture2D walk[4][4][3];
  Texture2D white[4][3];
  Texture2D death[4][7];
} AssetsPlayers;

void assets_players_load_textures();
void assets_players_load_player_textures(int player_id);
void assets_players_load_walk_textures(int player_id);
void assets_players_load_walk_white_textures();
void assets_players_load_death_textures(int player_id);

Texture2D *assets_players_get_walk_texture(int player_id,
                                           EntityDirection direction,
                                           int frame);
Texture2D *assets_players_get_walk_white_texture(EntityDirection direction,
                                                 int frame);
Texture2D *assets_players_get_death_texture(int player_id, int frame);

#endif
