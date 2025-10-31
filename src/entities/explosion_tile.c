#include "explosion_tile.h"
#include "core/animation.h"
#include "core/asset_manager.h"
#include "entities_manager.h"
#include <stdio.h>
#include <stdlib.h>

ExplosionTile *explosion_tile_create(Vector2 position,
                                     EntityDirection direction,
                                     ExplosionTileType tile_type) {
  Entity entity;
  entity.type = ENTITY_EXPLOSION_TILE;
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
  explosion_tile->tile_type = tile_type;
  explosion_tile->lifetime = 5.0f;
  explosion_tile->spawn_time = GetTime();

  animation_init(&explosion_tile->explosion_animation, 5, 0.5f, false, true);
  animation_play(&explosion_tile->explosion_animation);

  entities_manager_add((Entity *)explosion_tile);

  return explosion_tile;
}

void explosion_tile_update(Entity *self) {
  ExplosionTile *explosion_tile = (ExplosionTile *)self;

  animation_update(&explosion_tile->explosion_animation);

  if (GetTime() - explosion_tile->spawn_time >= explosion_tile->lifetime) {
    entities_manager_remove(self);
    return;
  }
}

void explosion_tile_draw(Entity *self) {
  ExplosionTile *explosion_tile = (ExplosionTile *)self;

  Texture2D *texture;

  if (explosion_tile->tile_type == EXPLOSION_CENTER) {
    texture = asset_manager_get_explosion_center_texture(
        explosion_tile->explosion_animation.current_frame);

  } else if (explosion_tile->tile_type == EXPLOSION_MIDDLE) {
    texture = asset_manager_get_explosion_middle_texture(
        explosion_tile->entity.direction,
        explosion_tile->explosion_animation.current_frame);
  } else {
    texture = asset_manager_get_explosion_final_texture(
        explosion_tile->entity.direction,
        explosion_tile->explosion_animation.current_frame);
  }

  DrawTexture(*texture, explosion_tile->entity.position.x,
              explosion_tile->entity.position.y, WHITE);
}

ExplosionTile *explosion_tile_at_grid(GridPosition grid) {
  for (int i = 0; i < MAX_ENTITIES; i++) {
    Entity *entity = entities_manager.entries[i];

    if (entity == NULL)
      break;

    ExplosionTile *explosion_tile = (ExplosionTile *)entity;

    if (entity->type == ENTITY_EXPLOSION_TILE) {
      GridPosition pos = map_world_to_grid(explosion_tile->entity.position);
      if (pos.col == grid.col && pos.row == grid.row)
        return explosion_tile;
    }
  }

  return NULL;
}
