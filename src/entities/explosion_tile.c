#include "explosion_tile.h"
#include "core/asset_manager.h"
#include "entities_manager.h"
#include "game/game_manager.h"
#include <stdlib.h>

ExplosionTile *explosion_tile_create(Vector2 position) {
  Entity entity;
  entity.type = ENTITY_EXPLOSION;
  entity.layer = LAYER_BOMBS;
  entity.position = position;
  entity.width = TILE_SIZE;
  entity.height = TILE_SIZE;
  entity.update = NULL;
  entity.draw = explosion_tile_draw;
  entity.debug = NULL;

  ExplosionTile *explosion_tile = malloc(sizeof(ExplosionTile));
  explosion_tile->entity = entity;

  entities_manager_add((Entity *)explosion_tile);

  return explosion_tile;
}

void explosion_tile_draw(Entity *self) {
  ExplosionTile *explosion_tile = (ExplosionTile *)self;

  DrawTexture(*asset_manager_get_explosion_texture(0),
              explosion_tile->entity.position.x,
              explosion_tile->entity.position.y, WHITE);
}