#include "ballom.h"
#include "core/animation.h"
#include "core/assets/assets_enemies.h"
#include "core/map.h"
#include "enemies/enemy.h"
#include "entities/entities_manager.h"
#include <stdlib.h>

Ballom *ballom_create(GridPosition spawn_grid) {
  Entity entity;
  entity.type = ENTITY_ENEMY;
  entity.layer = LAYER_PLAYERS;
  entity.direction = DIR_DOWN;
  entity.position = (Vector2){0, 0};
  entity.width = TILE_SIZE;
  entity.height = TILE_SIZE;
  entity.spawn_time = GetTime();
  entity.update = ballom_update;
  entity.draw = ballom_draw;
  entity.debug = NULL;

  entity.position = map_grid_to_world(spawn_grid);

  Enemy enemy;
  enemy.entity = entity;
  enemy.type = ENEMY_BALLOM;

  animation_init(&enemy.death_animation, 2, 0.05, true, false);
  animation_init(&enemy.walk_animation, 4, 0.01f, true, false);
  animation_play(&enemy.walk_animation);

  Ballom *ballom = malloc(sizeof(Ballom));
  ballom->enemy = enemy;

  entities_manager_add((Entity *)ballom);

  return ballom;
}

void ballom_update(Entity *self) {
  Ballom *ballom = (Ballom *)self;

  animation_update(&ballom->enemy.walk_animation);
}

void ballom_draw(Entity *self) {
  Ballom *ballom = (Ballom *)self;

  int frame = animation_get_frame(&ballom->enemy.walk_animation);

  Texture2D *texture =
      assets_enemies_get_ballom_texture(ballom->enemy.entity.direction, frame);

  DrawTexture(*texture, ballom->enemy.entity.position.x,
              ballom->enemy.entity.position.y, WHITE);
}
