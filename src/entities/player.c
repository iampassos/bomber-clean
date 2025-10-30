#include "player.h"
#include "core/asset_manager.h"
#include "core/map.h"
#include "entities/entities_manager.h"
#include "entity.h"
#include "game/game_manager.h"
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
  entity.width = 54;
  entity.height = 54;
  entity.update = player_update;
  entity.draw = player_draw;

  Player *player = malloc(sizeof(Player));
  player->entity = entity;
  player->id = id;
  player->bomb_capacity = 3;
  player->direction = DIR_DOWN;
  player->speed = 3.0f;

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

void player_update(Entity *self) {}

void player_draw(Entity *self) {
  Player *player = (Player *)self;

  Texture2D *texture = asset_manager_get_player_texture(player->direction, 0);

  DrawTexture(*texture, player->entity.position.x, player->entity.position.y,
              WHITE);
}
