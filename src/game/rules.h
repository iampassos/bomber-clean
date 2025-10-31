#ifndef RULES_H
#define RULES_H

#include "entities/player.h"
#include "entities/power_up.h"
#include <stdbool.h>

bool rules_can_place_bomb(Player *player);
bool rules_can_kill_player(Player *player);
bool rules_player_can_consume_power_up(Player *player, PowerUp* power_up);

#endif
