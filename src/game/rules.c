#include "rules.h"
#include "entities/entities_manager.h"
#include "entities/entity.h"
#include <stdlib.h>

bool rules_can_place_bomb(Player *player) {
  Entity *out[player->bomb_capacity];
  int count = entities_manager_get_all_player_bombs(player, out);

  if (count >= player->bomb_capacity)
    return false;

  return true;
}
