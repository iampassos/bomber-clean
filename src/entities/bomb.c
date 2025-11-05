#include "bomb.h"
#include "core/animation.h"
#include "core/assets/assets_maps.h"
#include "core/common.h"
#include "core/map.h"
#include "entities/entities_manager.h"
#include "entities/entity.h"
#include "game/game_manager.h"
#include <raylib.h>
#include <stdlib.h>

Bomb *bomb_create(int player_id, Vector2 position, int radius) {
  Entity entity;
  entity.type = ENTITY_BOMB;
  entity.layer = LAYER_BOMBS;
  entity.position = position;
  entity.width = TILE_SIZE;
  entity.height = TILE_SIZE;
  entity.spawn_time = GetTime();
  entity.height_tolerance = 0;
  entity.update = bomb_update;
  entity.draw = bomb_draw;
  entity.debug = NULL;

  Bomb *bomb = malloc(sizeof(Bomb));
  bomb->entity = entity;
  bomb->exploded = false;
  bomb->player_id = player_id;
  bomb->radius = radius;
  bomb->spawn_time = GetTime();
  bomb->explosion_time = 2.0f;

  animation_init(&bomb->tick_animation, 3, 0.2f, 1, false);
  animation_play(&bomb->tick_animation);

  entities_manager_add((Entity *)bomb);

  return bomb;
}

void bomb_update(Entity *self) {
  Bomb *bomb = (Bomb *)self;

  if (GetTime() - bomb->spawn_time >= bomb->explosion_time) {
    bomb->exploded = true;

    game_manager_on_bomb_exploded(map_world_to_grid(bomb->entity.position),
                                  bomb->radius, bomb->player_id);

    entities_manager_remove(self);
  }

  animation_update(&bomb->tick_animation);
}

void bomb_draw(Entity *self) {
  Bomb *bomb = (Bomb *)self;

  Texture2D *texture =
      assets_maps_get_bomb_texture(animation_get_frame(&bomb->tick_animation));

  DrawTexture(*texture, bomb->entity.position.x, bomb->entity.position.y,
              WHITE);
}

Bomb *bomb_at_grid(GridPosition grid) {
  for (int i = 0; i < entities_manager.count; i++) {
    Entity *entity = entities_manager.entries[i];

    if (entity->type == ENTITY_BOMB) {
      GridPosition pos = map_world_to_grid(entity->position);
      if (map_is_same_grid(pos, grid))
        return (Bomb *)entity;
    }
  }

  return NULL;
}
