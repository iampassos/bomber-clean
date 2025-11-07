#ifndef ASSETS_SOUNDS_H
#define ASSETS_SOUNDS_H

#include <raylib.h>

typedef struct {
  Sound bomb_explosion;
  Sound bomb_placement;
  Sound item_get;
  Sound enemy_death;
  Sound player_death;
  Sound player_walk[4];
  Sound stage_intro;
  Sound stage_clear;
} AssetsSounds;

void assets_sounds_load_sounds();

Sound *assets_sounds_get_bomb_explosion();
Sound *assets_sounds_get_bomb_placement();
Sound *assets_sounds_get_item_get();
Sound *assets_sounds_get_enemy_death();
Sound *assets_sounds_get_player_death();
Sound *assets_sounds_get_player_walk(int i);
Sound *assets_sounds_get_stage_intro();
Sound *assets_sounds_get_stage_clear();

#endif
