#include "player.h"
#include "core/animation.h"
#include "core/asset_manager.h"
#include "core/common.h"
#include "core/map.h"
#include "core/physics.h"
#include "entities/entities_manager.h"
#include "entity.h"
#include "game/game_manager.h"
#include "render/input_manager.h"
#include <math.h>
#include <raylib.h>
#include <stdlib.h>

#define HEIGHT_TOLERANCE 28.5f

Vector2 player_grid_to_world(Player *player, GridPosition pos) {
  Vector2 center = map_grid_to_world_center(pos);
  return (Vector2){center.x - player->entity.width / 2,
                   center.y - player->entity.height / 2 - HEIGHT_TOLERANCE};
}

GridPosition player_grid(Player *player) {
  Vector2 feet_position =
      (Vector2){player->entity.position.x + player->entity.width / 2.0f,
                player->entity.position.y +
                    (player->direction == DIR_UP
                         ? player->entity.height * 1.1f
                         : player->entity.height * 0.60f + HEIGHT_TOLERANCE)};
  GridPosition pos = map_world_to_grid(feet_position);
  return pos;
}

Player *player_create(int id, Vector2 position) {
  Entity entity;
  entity.position = position;
  entity.width = TILE_SIZE - 10;
  entity.height = TILE_SIZE - 10;
  entity.update = player_update;
  entity.draw = player_draw;

  Player *player = malloc(sizeof(Player));
  player->entity = entity;
  player->id = id;
  player->bomb_capacity = 3;
  player->direction = DIR_DOWN;
  player->speed = 3.0f;
  player->input = (PlayerInput){{0}, false};

  animation_init(&player->walk_animation, 3, 0.25f, 1);
  animation_play(&player->walk_animation);

  GridPosition pos = map_world_to_grid(position);
  pos.col = fmax(1, fmin(pos.col, GRID_WIDTH - 2));
  pos.row = fmax(1, fmin(pos.row, GRID_HEIGHT - 2));

  Map *map = &game_manager.map;

  entities_manager_add((Entity *)player);

  if (map_is_walkable(map, pos)) {
    player->entity.position = player_grid_to_world(player, pos);
    return player;
  }

  for (int r = pos.col; r < GRID_HEIGHT - 1; r++) {
    for (int c = pos.row; c < GRID_WIDTH - 1; c++) {
      if (map_is_walkable(map, (GridPosition){r, c})) {
        player->entity.position =
            player_grid_to_world(player, (GridPosition){c, r});
        return player;
      }
    }
  }

  player->entity.position = player_grid_to_world(player, (GridPosition){1, 1});

  return player;
}

void player_update(Entity *self) {
  Player *player = (Player *)self;
  player->input = game_manager.players[0].input;

  Vector2 projected = player->entity.position;

  projected.x = fmax(MAP_X_OFFSET, player->entity.position.x +
                                       player->speed * player->input.move.x);
  projected.y = fmax(MAP_Y_OFFSET, player->entity.position.y +
                                       player->speed * player->input.move.y);

  Vector2 new_pos = player->entity.position;

  Vector2 horizontal = {projected.x,
                        player->entity.position.y + HEIGHT_TOLERANCE};
  if (physics_can_move_to(horizontal, player->entity.width,
                          player->entity.height))
    new_pos.x = horizontal.x;

  Vector2 vertical = {player->entity.position.x, projected.y};
  if (physics_can_move_to((Vector2){vertical.x, vertical.y + HEIGHT_TOLERANCE},
                          player->entity.width, player->entity.height))
    new_pos.y = vertical.y;

  float dx = new_pos.x - player->entity.position.x;
  float dy = new_pos.y - player->entity.position.y;

  if (fabs(dx) > fabs(dy)) {
    player->direction = dx > 0 ? DIR_RIGHT : DIR_LEFT;
    player->state = STATE_RUNNING;
    animation_update(&player->walk_animation);
  } else if (fabs(dy) > 0.0f) {
    player->direction = dy > 0 ? DIR_DOWN : DIR_UP;
    player->state = STATE_RUNNING;
    animation_update(&player->walk_animation);
  } else if (fabs(dy) == 0.0f && fabs(dx) == 0.0f) {
    player->state = STATE_IDLE;
    player->walk_animation.current_frame = 1;
  }

  player->entity.position = new_pos;
}

void player_draw(Entity *self) {
  Player *player = (Player *)self;

  Texture2D *texture = asset_manager_get_player_texture(
      player->direction, animation_get_frame(&player->walk_animation));

  DrawTexture(*texture, player->entity.position.x, player->entity.position.y,
              WHITE);
}
