#include "rules.h"
#include "core/map.h"
#include "entities/entities_manager.h"
#include "entities/player.h"
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
