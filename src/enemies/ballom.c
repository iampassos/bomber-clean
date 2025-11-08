#include "ballom.h"
#include "core/animation.h"
#include "core/assets/assets_enemies.h"
#include "core/assets/assets_sounds.h"
#include "core/common.h"
#include "core/map.h"
#include "core/physics.h"
#include "enemies/enemy.h"
#include "entities/entities_manager.h"
#include "entities/entity.h"
#include "game/game_manager.h"
#include <math.h>
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
  enemy.speed = 2.0f * 60.0f;
  enemy.alive = false;
  enemy.type = ENEMY_BALLOM;

  animation_init(&enemy.death_animation, (int[]){0, 1}, 2, 0.01f, true, false);
  animation_init(&enemy.spawn_animation, (int[]){0, 1}, 2, 0.01f, true, true);
  animation_init(&enemy.walk_animation, (int[]){0, 1, 2, 3}, 4, 0.01, true,
                 true);

  Ballom *ballom = malloc(sizeof(Ballom));
  ballom->enemy = enemy;

  ballom->enemy.entity.position =
      entity_grid_to_world(&ballom->enemy.entity, spawn_grid);

  entities_manager_add((Entity *)ballom);

  return ballom;
}

void ballom_update(Entity *self) {
  Enemy *enemy = (Enemy *)self;

  animation_update(&enemy->walk_animation);

  if (!animation_is_finished(&enemy->spawn_animation)) {
    self->direction = DIR_DOWN;
    animation_update(&enemy->spawn_animation);

    if (animation_elapsed(&enemy->spawn_animation) >
        MACHINE_SPAWN_ANIMATION_TIME) {
      animation_finish(&enemy->spawn_animation);
      enemy->alive = true;
    }

    return;
  }

  if (!enemy->alive) {
    if (enemy->death_animation.playing) {
      if (animation_elapsed(&enemy->death_animation) >= 1.0f) {
        entities_manager_remove(self);
      } else
        animation_update(&enemy->death_animation);
    } else {
      PlaySound(*assets_sounds_get_enemy_death());
      animation_play(&enemy->death_animation);
    }
    return;
  }

  EntityDirection dir = self->direction;
  Vector2 position = self->position;
  Vector2 projected = position;

  projected.x =
      position.x + (dir == DIR_LEFT    ? -enemy->speed * game_manager.dt
                    : dir == DIR_RIGHT ? enemy->speed * game_manager.dt
                                       : 0);
  projected.y =
      (position.y + (dir == DIR_UP     ? -enemy->speed * game_manager.dt
                     : dir == DIR_DOWN ? enemy->speed * game_manager.dt
                                       : 0));

  if (physics_can_move_to_entities(
          self, (Vector2){projected.x, projected.y + BALLOM_HEIGHT_TOLERANCE},
          false))
    position = projected;
  else {
    EntityDirection new_dir = rand() % 4;

    projected.x =
        position.x + (new_dir == DIR_LEFT    ? -enemy->speed * game_manager.dt
                      : new_dir == DIR_RIGHT ? enemy->speed * game_manager.dt
                                             : 0);
    projected.y =
        position.y + (new_dir == DIR_UP     ? -enemy->speed * game_manager.dt
                      : new_dir == DIR_DOWN ? enemy->speed * game_manager.dt
                                            : 0);

    if (physics_can_move_to_entities(
            self, (Vector2){projected.x, projected.y + BALLOM_HEIGHT_TOLERANCE},
            false))
      self->direction = new_dir;
  }

  self->position = position;
}

void ballom_draw(Entity *self) {
  Enemy *enemy = (Enemy *)self;

  int frame = enemy->walk_animation.frame_index;

  Texture2D *texture =
      enemy->death_animation.frame_index == 0 &&
              enemy->spawn_animation.frame_index % 2 == 1
          ? assets_enemies_get_normal_ballom_texture(self->direction, frame)
          : assets_enemies_get_white_ballom_texture(self->direction, frame);

  frame = enemy->spawn_animation.frame_index;

  DrawTexture(*texture, self->position.x,
              (enemy->spawn_animation.playing
                   ? (MACHINE_SPAWN_ANIMATION_TICKS -
                      fmin(animation_total_ticks(&enemy->spawn_animation),
                           MACHINE_SPAWN_ANIMATION_TICKS)) *
                         -5.0f * 60.0f * game_manager.dt
                   : 0.0f) +
                  enemy->entity.position.y,
              WHITE);
}
