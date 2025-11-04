#include "ballom.h"
#include "core/animation.h"
#include "core/assets/assets_enemies.h"
#include "core/common.h"
#include "core/map.h"
#include "core/physics.h"
#include "enemies/enemy.h"
#include "entities/entities_manager.h"
#include "entities/entity.h"
#include <stdlib.h>

#define HEIGHT_TOLERANCE 28.5f

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

  Enemy enemy;
  enemy.entity = entity;
  enemy.type = ENEMY_BALLOM;

  animation_init(&enemy.death_animation, 2, 0.05, true, false);
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

  GridPosition grid = entity_world_to_grid(entity, BALLOM_HEIGHT_TOLERANCE);

  Vector2 dirs[] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

  EntityDirection dir = entity->direction;

  GridPosition next_grid = {grid.col + dirs[dir].x, grid.row + dirs[dir].y};

  Vector2 position = entity->position;

  Vector2 projected = position;

  projected.x = position.x + (dir == DIR_LEFT    ? -ENEMY_DEFAULT_SPEED
                              : dir == DIR_RIGHT ? ENEMY_DEFAULT_SPEED
                                                 : 0);
  projected.y = position.y + (dir == DIR_UP     ? -ENEMY_DEFAULT_SPEED
                              : dir == DIR_DOWN ? ENEMY_DEFAULT_SPEED
                                                : 0);

  if (physics_can_move_to(
          (Vector2){entity->position.x, projected.y + BALLOM_HEIGHT_TOLERANCE},
          entity->width, entity->height))
    position = projected;
  ;

  entity->position = position;

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
