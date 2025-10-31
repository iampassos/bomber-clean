#include "explosion_tile.h"
#include "core/asset_manager.h"
#include "entities_manager.h"
#include <stdlib.h>

ExplosionTile *explosion_tile_create(Vector2 position, EntityDirection direction, bool center) {
  Entity entity;
  entity.type = ENTITY_EXPLOSION;
  entity.layer = LAYER_BOMBS;
  entity.direction = direction;
  entity.position = position;
  entity.width = TILE_SIZE;
  entity.height = TILE_SIZE;
  entity.update = explosion_tile_update;
  entity.draw = explosion_tile_draw;
  entity.debug = NULL;

  ExplosionTile *explosion_tile = malloc(sizeof(ExplosionTile));
  explosion_tile->entity = entity;
  explosion_tile->center = center;
  explosion_tile->lifetime = 1.0f;
  explosion_tile->spawn_time = GetTime();

  entities_manager_add((Entity *)explosion_tile);

  return explosion_tile;
}

void explosion_tile_update(Entity *self) {
  ExplosionTile *explosion_tile = (ExplosionTile *)self;

  if (GetTime() - explosion_tile->spawn_time >= explosion_tile->lifetime)
    entities_manager_remove(self);
}

void explosion_tile_draw(Entity *self) {
  ExplosionTile *explosion_tile = (ExplosionTile *)self;

  // DrawTexture(*asset_manager_get_explosion_texture(0),
  //             explosion_tile->entity.position.x,
  //             explosion_tile->entity.position.y, WHITE);
}
