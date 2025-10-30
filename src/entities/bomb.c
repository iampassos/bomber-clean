#include "bomb.h"
#include "core/asset_manager.h"
#include "core/common.h"
#include "core/map.h"
#include "entities/entities_manager.h"
#include "game/game_manager.h"
#include <raylib.h>
#include <stdlib.h>

Bomb *bomb_create(int player_id, Vector2 position, float radius) {
  Entity entity;
  entity.position = position;
  entity.width = TILE_SIZE;
  entity.height = TILE_SIZE;
  entity.update = bomb_update;
  entity.draw = bomb_draw;

  Bomb *bomb = malloc(sizeof(Bomb));
  bomb->entity = entity;
  bomb->player_id = player_id;
  bomb->radius = radius;
  bomb->spawn_time = GetTime();

  entities_manager_add((Entity *)bomb);

  return bomb;
}

void bomb_update(Entity *self) { Bomb *bomb = (Bomb *)self; }

void bomb_draw(Entity *self) {
  Bomb *bomb = (Bomb *)self;

  Texture2D *texture = asset_manager_get_bomb_texture(0);

  DrawTexture(*texture, bomb->entity.position.x, bomb->entity.position.y,
              WHITE);
}
