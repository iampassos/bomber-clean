#include "assets_sounds.h"
#include "core/assets/asset_manager.h"
#include <raylib.h>

void assets_sounds_load_sounds() {
  asset_manager.assets_sounds.bomb_explosion =
      LoadSound("assets/sounds/Bomb Explodes.wav");
  asset_manager.assets_sounds.bomb_placement =
      LoadSound("assets/sounds/Place Bomb.wav");
  SetSoundVolume(asset_manager.assets_sounds.bomb_placement, 0.25f);
  asset_manager.assets_sounds.item_get =
      LoadSound("assets/sounds/Item Get.wav");
  asset_manager.assets_sounds.enemy_death =
      LoadSound("assets/sounds/Enemy Dies.wav");
  asset_manager.assets_sounds.player_death =
      LoadSound("assets/sounds/Bomberman Dies.wav");
  asset_manager.assets_sounds.stage_intro =
      LoadSound("assets/sounds/Stage Intro.wav");
  asset_manager.assets_sounds.stage_clear =
      LoadSound("assets/sounds/Stage Clear.wav");

  for (int i = 0; i < 4; i++) {
    asset_manager.assets_sounds.player_walk[i] =
        LoadSound("assets/sounds/Walking 2.wav");
    SetSoundVolume(asset_manager.assets_sounds.player_walk[i], 0.25f);
  }
}

void assets_sounds_unload_all() {
  UnloadSound(asset_manager.assets_sounds.bomb_explosion);
  UnloadSound(asset_manager.assets_sounds.bomb_placement);
  UnloadSound(asset_manager.assets_sounds.item_get);
  UnloadSound(asset_manager.assets_sounds.enemy_death);
  UnloadSound(asset_manager.assets_sounds.player_death);

  for (int i = 0; i < 4; i++)
    UnloadSound(asset_manager.assets_sounds.player_walk[i]);

  UnloadSound(asset_manager.assets_sounds.stage_intro);
  UnloadSound(asset_manager.assets_sounds.stage_clear);
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

Sound *assets_sounds_get_player_death() {
  return &asset_manager.assets_sounds.player_death;
}

Sound *assets_sounds_get_player_walk(int i) {
  return &asset_manager.assets_sounds.player_walk[i];
}

Sound *assets_sounds_get_stage_intro() {
  return &asset_manager.assets_sounds.stage_intro;
}

Sound *assets_sounds_get_stage_clear() {
  return &asset_manager.assets_sounds.stage_clear;
}
