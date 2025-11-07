#ifndef ASSETS_SOUNDS_H
#define ASSETS_SOUNDS_H

#include <raylib.h>

typedef struct {
  Sound bomb_explosion;
  Sound bomb_placement;
  Sound item_get;
  Sound enemy_death;
  Sound stage_intro;
} AssetsSounds;

void assets_sounds_load_sounds();

Sound *assets_sounds_get_bomb_explosion();
Sound *assets_sounds_get_bomb_placement();
Sound *assets_sounds_get_item_get();
Sound *assets_sounds_get_enemy_death();
Sound *assets_sounds_get_stage_intro();

#endif
