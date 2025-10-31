#include "power_up.h"
#include "core/asset_manager.h"
#include "entities_manager.h"
#include "game/game_manager.h"
#include "player.h"
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

PowerUp *power_up_create(Vector2 position, PowerUpType type) {
  Entity entity;
  entity.type = ENTITY_POWER_UP;
  entity.layer = LAYER_BOMBS;
  entity.position = position;
  entity.width = TILE_SIZE;
  entity.height = TILE_SIZE;
  entity.update = power_up_update;
  entity.draw = power_up_draw;
  entity.debug = power_up_debug;

  PowerUp *power_up = malloc(sizeof(PowerUp));
  power_up->entity = entity;
  power_up->power_up_type = type;
  power_up->spawn_time = GetTime();

  animation_init(&power_up->tick_animation, 10, 0.1f, 0);

  entities_manager_add((Entity *)power_up);

  return power_up;
}

void power_up_update(Entity *self) {
  PowerUp *power_up = (PowerUp *)self;

  Player *player = player_on_grid(map_world_to_grid(power_up->entity.position));

  if (player) {
    game_manager_on_power_up_press(player, power_up);
    return;
  }

  if (GetTime() - power_up->spawn_time >= POWER_UP_MAX_TIME) {
    entities_manager_remove(self);
    return;
  }

  if (GetTime() - power_up->spawn_time >= POWER_UP_MAX_TIME - 1.0f &&
      !animation_is_playing(&power_up->tick_animation))
    animation_play(&power_up->tick_animation);

  if (animation_is_playing(&power_up->tick_animation))
    animation_update(&power_up->tick_animation);
}

void power_up_draw(Entity *self) {
  PowerUp *power_up = (PowerUp *)self;

  Texture2D *texture =
      asset_manager_get_power_up_texture(power_up->power_up_type);

  DrawTexture(*texture, power_up->entity.position.x,
              power_up->entity.position.y,
              animation_is_playing(&power_up->tick_animation) &&
                      power_up->tick_animation.current_frame % 2 == 0
                  ? BLANK
                  : WHITE);
}

void power_up_debug(Entity *self) {
  PowerUp *power_up = (PowerUp *)self;

  char buff[100];
  snprintf(buff, sizeof(buff), "%.2f", GetTime() - power_up->spawn_time);

  Vector2 textSize = MeasureTextEx(GetFontDefault(), buff, 20, 1.0f);
  DrawTextEx(GetFontDefault(), buff,
             (Vector2){power_up->entity.position.x,
                       power_up->entity.position.y - textSize.y},
             20, 1.0f, WHITE);
}