#include "ballom.h"
#include "core/animation.h"
#include "core/assets/assets_enemies.h"
#include "core/common.h"
#include "core/map.h"
#include "core/physics.h"
#include "enemies/enemy.h"
#include "entities/entities_manager.h"
#include "entities/entity.h"
#include <raylib.h>
#include <stdlib.h>

Ballom *ballom_create(GridPosition spawn_grid) {
  Entity entity;
  entity.type = ENTITY_ENEMY;
  entity.layer = LAYER_PLAYERS;
  entity.direction = DIR_UP;
  entity.position = (Vector2){0, 0};
  entity.width = TILE_SIZE;
  entity.height = TILE_SIZE;
  entity.spawn_time = GetTime();
  entity.height_tolerance = BALLOM_HEIGHT_TOLERANCE;
  entity.update = ballom_update;
  entity.draw = ballom_draw;
  entity.debug = NULL;

  Enemy enemy;
  enemy.entity = entity;
  enemy.speed = 2.0f;
  enemy.alive = true;
  enemy.type = ENEMY_BALLOM;

  animation_init(&enemy.death_animation, 2, 0.01, true, false);

  animation_init(&enemy.spawn_animation, 25, 0.01, false, false);
  animation_play(&enemy.spawn_animation);

  animation_init(&enemy.walk_animation, 4, 0.01f, true, false);
  animation_play(&enemy.walk_animation);

  Ballom *ballom = malloc(sizeof(Ballom));
  ballom->enemy = enemy;

  ballom->enemy.entity.position = entity_grid_to_world(
      &ballom->enemy.entity, spawn_grid, BALLOM_HEIGHT_TOLERANCE);

  entities_manager_add((Entity *)ballom);

  return ballom;
}

void ballom_update(Entity *self) {
  Ballom *ballom = (Ballom *)self;
  Entity *entity = (Entity *)&ballom->enemy.entity;

  if (animation_is_playing(&ballom->enemy.spawn_animation)) {
    entity->direction = DIR_DOWN;
    animation_update(&ballom->enemy.spawn_animation);
    return;
  }

  if (!ballom->enemy.alive) {
    if (!animation_is_playing(&ballom->enemy.death_animation))
      animation_play(&ballom->enemy.death_animation);
    else {
      if (GetTime() - animation_started_at(&ballom->enemy.death_animation) >=
          1.0f)
        entities_manager_remove(self);
      else
        animation_update(&ballom->enemy.death_animation);
    }
    return;
  }

  animation_update(&ballom->enemy.walk_animation);

  if (GetTime() - animation_started_at(&ballom->enemy.spawn_animation) < 1.0f)
    return;

  EntityDirection dir = entity->direction;
  Vector2 position = entity->position;
  Vector2 projected = position;

  projected.x = position.x + (dir == DIR_LEFT    ? -ballom->enemy.speed
                              : dir == DIR_RIGHT ? ballom->enemy.speed
                                                 : 0);
  projected.y = position.y + (dir == DIR_UP     ? -ballom->enemy.speed
                              : dir == DIR_DOWN ? ballom->enemy.speed
                                                : 0);

  if (physics_can_move_to(
          (Vector2){projected.x, projected.y + BALLOM_HEIGHT_TOLERANCE},
          entity->width, entity->height))
    position = projected;
  else {
    EntityDirection new_dir = rand() % 4;

    projected.x = position.x + (new_dir == DIR_LEFT    ? -ballom->enemy.speed
                                : new_dir == DIR_RIGHT ? ballom->enemy.speed
                                                       : 0);
    projected.y = position.y + (new_dir == DIR_UP     ? -ballom->enemy.speed
                                : new_dir == DIR_DOWN ? ballom->enemy.speed
                                                      : 0);

    if (physics_can_move_to(
            (Vector2){projected.x, projected.y + BALLOM_HEIGHT_TOLERANCE},
            entity->width, entity->height))
      entity->direction = new_dir;
  }

  entity->position = position;
}

void ballom_draw(Entity *self) {
  Ballom *ballom = (Ballom *)self;

  int frame = animation_get_frame(&ballom->enemy.walk_animation);

  Texture2D *texture =
      animation_get_frame(&ballom->enemy.death_animation) == 0 &&
              animation_get_frame(&ballom->enemy.spawn_animation) % 2 == 0
          ? assets_enemies_get_normal_ballom_texture(
                ballom->enemy.entity.direction, frame)
          : assets_enemies_get_white_ballom_texture(
                ballom->enemy.entity.direction, frame);

  frame = animation_get_frame(&ballom->enemy.spawn_animation);

  DrawTexture(*texture, ballom->enemy.entity.position.x,
              (animation_is_playing(&ballom->enemy.spawn_animation)
                   ? (25 - frame) * -5.0f
                   : 0) +
                  ballom->enemy.entity.position.y,
              WHITE);
}
