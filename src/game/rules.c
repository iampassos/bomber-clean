#include "rules.h"
#include "core/common.h"
#include "enemies/enemy.h"
#include "entities/bomb.h"
#include "entities/entities_manager.h"
#include "entities/entity.h"
#include "entities/player.h"
#include "entities/power_up.h"
#include "game/game_manager.h"
#include <time.h>

bool rules_can_place_bomb(Player *player) {
  if (!player->alive)
    return false;

  if (player_get_all_bombs(player, NULL) >= player->bomb_capacity)
    return false;

  GridPosition pos = entity_world_to_grid(&player->entity);

  if (!map_is_walkable(game_manager.map, pos))
    return false;

  if (entities_manager_get_all_at_grid(pos, NULL, MAX_ENTITIES) > 1)
    return false;

  return true;
}

bool rules_can_kill_player(Player *player) {
  if (!player->invencible)
    return true;

  return false;
}

bool rules_can_kill_power_up(PowerUp *power_up) {
  if (power_up->active)
    return true;

  return false;
}

bool rules_can_kill_enemy(Enemy *enemy) {
  if (enemy->alive)
    return true;

  return false;
}

bool rules_can_spawn_enemy(GridPosition grid) {
  if (entities_manager_get_all_from_type(ENTITY_ENEMY, NULL, ENEMY_MAP_LIMIT) >=
      ENEMY_MAP_LIMIT)
    return false;

  TileType tile = map_get_tile(game_manager.map, grid);

  if (!map_is_valid_grid(grid))
    return false;

  if (tile != TILE_EMPTY)
    return false;

  if (player_at_grid(grid) != NULL)
    return false;

  for (int i = grid.col - 1; i <= grid.col + 1; i++) {
    for (int j = grid.row - 1; j <= grid.row + 1; j++) {
      if (enemy_at_grid((GridPosition){i, j}))
        return false;
      if (player_at_grid((GridPosition){i, j}))
        return false;
    }
  }

  return true;
}

bool rules_can_spawn_power_up(GridPosition grid) {
  if (entities_manager_get_all_from_type(
          ENTITY_POWER_UP, NULL, POWER_UP_MAP_LIMIT) >= POWER_UP_MAP_LIMIT)
    return false;

  TileType tile = map_get_tile(game_manager.map, grid);

  if (!map_is_valid_grid(grid))
    return false;

  if (tile != TILE_EMPTY)
    return false;

  for (int i = grid.col - 1; i <= grid.col + 1; i++) {
    for (int j = grid.row - 1; j <= grid.row + 1; j++) {
      if (power_up_at_grid((GridPosition){i, j}))
        return false;
    }
  }

  return true;
}

bool rules_player_can_consume_power_up(Player *player, PowerUp *power_up) {
  switch (power_up->power_up_type) {
  case POWER_UP_LIFE:
    if (player->lives + 1 > MAX_PLAYER_LIVES)
      return false;
    break;
  case POWER_UP_SPEED:
    if (player->speed + POWER_UP_SPEED_INCREASE >
        MAX_PLAYER_SPEED + POWER_UP_SPEED_INCREASE / 2.0f)
      return false;
    break;
  case POWER_UP_BOMB:
    if (player->bomb_capacity + 1 > MAX_PLAYER_BOMBS)
      return false;
    break;
  case POWER_UP_RADIUS:
    if (player->bomb_radius + 1 > MAX_BOMB_RADIUS)
      return false;
    ;
    break;
  case POWER_UP_MAXIMUM_RADIUS:
    break;
  case POWER_UP_INVENCIBLE:
    break;
  }

  return true;
}

bool rules_can_spawn_bomb(GridPosition grid) {
  TileType tile = map_get_tile(game_manager.map, grid);

  if (!map_is_valid_grid(grid))
    return false;

  if (tile != TILE_EMPTY)
    return false;

  for (int i = grid.col - 1; i <= grid.col + 1; i++) {
    for (int j = grid.row - 1; j <= grid.row + 1; j++) {
      if (bomb_at_grid((GridPosition){i, j}))
        return false;
      if (player_at_grid((GridPosition){i, j}))
        return false;
    }
  }

  return true;
}
