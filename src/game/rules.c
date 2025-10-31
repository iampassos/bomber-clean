#include "rules.h"
#include "core/map.h"
#include "entities/entities_manager.h"
#include "entities/explosion_tile.h"
#include "game/game_manager.h"
#include <stdlib.h>

bool rules_can_place_bomb(Player *player) {
  if (!player->alive)
    return false;

  if (player_get_all_bombs(player, NULL) >= player->bomb_capacity)
    return false;

  GridPosition pos = player_world_to_grid(player);

  if (!map_is_walkable(&game_manager.map, pos))
    return false;

  if (entities_manager_get_all_at_grid(pos, NULL, MAX_ENTITIES) > 0)
    return false;

  return true;
}

bool rules_can_kill_player(Player *player) {
  GridPosition pos = player_world_to_grid(player);

  if (explosion_tile_at_grid(pos) != NULL)
    return true;

  return false;
}

bool rules_player_can_consume_power_up(Player *player, PowerUp *power_up) {
  switch (power_up->power_up_type) {
  case POWER_UP_LIFE:
    if (player->lives + 1 > MAX_PLAYER_LIVES)
      return false;
    break;
  case POWER_UP_SPEED:
    if (player->speed + POWER_UP_SPEED_INCREASE > MAX_PLAYER_SPEED + POWER_UP_SPEED_INCREASE / 2.0f)
      return false;
    break;
  case POWER_UP_BOMB:
    if (player->bomb_capacity + 1 > MAX_PLAYER_BOMBS)
      return false;
    break;
  }

  return true;
}