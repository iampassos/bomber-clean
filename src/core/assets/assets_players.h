#ifndef ASSETS_PLAYERS_H
#define ASSETS_PLAYERS_H

#include "entities/entity.h"
#include <raylib.h>

typedef struct {
  Texture2D walk[4][3];
  Texture2D white[4][3];
  Texture2D death[7];
} AssetsPlayers;

void assets_players_load_textures();
void assets_players_load_walk_textures();
void assets_players_load_walk_white_textures();
void assets_players_load_death_textures();

Texture2D *assets_players_get_walk_texture(EntityDirection direction,
                                           int frame);
Texture2D *assets_players_get_walk_white_texture(EntityDirection direction,
                                                 int frame);
Texture2D *assets_players_get_death_texture(int frame);

#endif
