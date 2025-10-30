#include "bomb.h"
#include "core/animation.h"
#include "core/asset_manager.h"
#include "core/common.h"
#include "entities/entities_manager.h"
#include <raylib.h>
#include <stdlib.h>

Bomb *bomb_create(int player_id, Vector2 position, float radius) {
  Entity entity;
  entity.type = ENTITY_BOMB;
  entity.position = position;
  entity.width = TILE_SIZE;
  entity.height = TILE_SIZE;
  entity.update = bomb_update;
  entity.draw = bomb_draw;
  entity.debug = NULL;

  Bomb *bomb = malloc(sizeof(Bomb));
  bomb->entity = entity;
  bomb->player_id = player_id;
  bomb->radius = radius;
  bomb->spawn_time = GetTime();

  animation_init(&bomb->tick_animation, 3, 1.0f, 1);
  animation_play(&bomb->tick_animation);

  entities_manager_add((Entity *)bomb);

  return bomb;
}

void bomb_update(Entity *self) {
  Bomb *bomb = (Bomb *)self;
  animation_update(&bomb->tick_animation);
}

void bomb_draw(Entity *self) {
  Bomb *bomb = (Bomb *)self;

  Texture2D *texture = asset_manager_get_bomb_texture(
      animation_get_frame(&bomb->tick_animation));

  DrawTexture(*texture, bomb->entity.position.x, bomb->entity.position.y,
              WHITE);
}
