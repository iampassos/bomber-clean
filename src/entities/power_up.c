#include "power_up.h"
#include "core/animation.h"
#include "core/assets/asset_manager.h"
#include "core/assets/assets_maps.h"
#include "core/common.h"
#include "entities/entity.h"
#include "entities_manager.h"
#include "game/game_manager.h"
#include "player.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

PowerUp *power_up_create(Vector2 position, PowerUpType type) {
  Entity entity;
  entity.type = ENTITY_POWER_UP;
  entity.layer = LAYER_POWER_UPS;
  entity.position = position;
  entity.width = TILE_SIZE;
  entity.height = TILE_SIZE;
  entity.spawn_time = GetTime();
  entity.height_tolerance = 0;
  entity.update = power_up_update;
  entity.draw = power_up_draw;
  entity.debug = power_up_debug;

  PowerUp *power_up = malloc(sizeof(PowerUp));
  power_up->active = true;
  power_up->entity = entity;
  power_up->power_up_type = type;

  animation_init(&power_up->tick_animation, (int[]){0, 1}, 2, 0.05f, true,
                 true);
  animation_init(&power_up->explosion_animation, (int[]){0, 1, 3, 4, 5, 6}, 7,
                 0.125f, false, false);

  entities_manager_add((Entity *)power_up);

  return power_up;
}

void power_up_update(Entity *self) {
  PowerUp *power_up = (PowerUp *)self;

  if (!power_up->active) {
    if (animation_is_finished(&power_up->explosion_animation)) {
      entities_manager_remove(self);
    } else {
      if (!power_up->explosion_animation.playing)
        animation_play(&power_up->explosion_animation);
      animation_update(&power_up->explosion_animation);
    }
    return;
  }

  Player *player = player_at_grid(map_world_to_grid(power_up->entity.position));
  if (player) {
    game_manager_on_power_up_press(player, power_up);
    return;
  }

  if (GetTime() - power_up->entity.spawn_time >= POWER_UP_TIMEOUT) {
    entities_manager_remove(self);
    return;
  }

  animation_update(&power_up->tick_animation);
}

void power_up_draw(Entity *self) {
  PowerUp *power_up = (PowerUp *)self;

  Texture2D *texture =
      power_up->active
          ? asset_manager_get_power_up_texture(
                power_up->power_up_type, power_up->tick_animation.frame_index)
          : assets_maps_get_power_up_explosion_texture(
                power_up->explosion_animation.frame_index);

  DrawTexture(*texture, power_up->entity.position.x,
              power_up->entity.position.y, WHITE);
}

void power_up_debug(Entity *self) {
  PowerUp *power_up = (PowerUp *)self;

  char buff[100];
  snprintf(buff, sizeof(buff), "%.2f", GetTime() - power_up->entity.spawn_time);

  Vector2 textSize = MeasureTextEx(GetFontDefault(), buff, 20, 1.0f);
  DrawTextEx(GetFontDefault(), buff,
             (Vector2){power_up->entity.position.x,
                       power_up->entity.position.y - textSize.y},
             20, 1.0f, WHITE);
}

PowerUp *power_up_at_grid(GridPosition grid) {
  for (int i = 0; i < entities_manager.count; i++) {
    Entity *entity = entities_manager.entries[i];

    if (entity->type == ENTITY_POWER_UP) {
      GridPosition pos = map_world_to_grid(entity->position);
      if (map_is_same_grid(pos, grid))
        return (PowerUp *)entity;
    }
  }

  return NULL;
}
