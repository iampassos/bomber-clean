#include "assets_sounds.h"
#include "core/assets/asset_manager.h"
#include <raylib.h>

void assets_sounds_load_sounds() {
  asset_manager.assets_sounds.bomb_explosion =
      LoadSound("assets/sounds/Bomb Explodes.wav");
  asset_manager.assets_sounds.bomb_placement =
      LoadSound("assets/sounds/Place Bomb.wav");
  asset_manager.assets_sounds.item_get =
      LoadSound("assets/sounds/Item Get.wav");
  asset_manager.assets_sounds.enemy_death =
      LoadSound("assets/sounds/Enemy Dies.wav");
  asset_manager.assets_sounds.stage_intro =
      LoadSound("assets/sounds/Stage Intro.wav");
}

Sound *assets_sounds_get_bomb_explosion() {
  return &asset_manager.assets_sounds.bomb_explosion;
}

Sound *assets_sounds_get_bomb_placement() {
  return &asset_manager.assets_sounds.bomb_placement;
}

Sound *assets_sounds_get_item_get() {
  return &asset_manager.assets_sounds.item_get;
}
Sound *assets_sounds_get_enemy_death() {
  return &asset_manager.assets_sounds.enemy_death;
}

Sound *assets_sounds_get_stage_intro() {
  return &asset_manager.assets_sounds.stage_intro;
}
