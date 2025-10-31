#include "power_up.h"
#include "core/asset_manager.h"
#include "entities_manager.h"
#include <raylib.h>
#include <stdlib.h>

PowerUp *power_up_create(Vector2 position, PowerUpType type) {
  Entity entity;
  entity.type = ENTITY_POWER_UP;
  entity.layer = LAYER_BOMBS;
  entity.position = position;
  entity.width = TILE_SIZE;
  entity.height = TILE_SIZE;
  entity.update = power_up_update;
  entity.draw = power_up_draw;
  entity.debug = NULL;

  PowerUp *power_up = malloc(sizeof(PowerUp));
  power_up->entity = entity;
  power_up->power_up_type = type;

  entities_manager_add((Entity *)power_up);

  return power_up;
}

void power_up_update(Entity *self) { PowerUp *power_up = (PowerUp *)self; }

void power_up_draw(Entity *self) {
  PowerUp *power_up = (PowerUp *)self;

  Texture2D *texture =
      asset_manager_get_power_up_texture(power_up->power_up_type);

  DrawTexture(*texture, power_up->entity.position.x,
              power_up->entity.position.y, WHITE);
}
