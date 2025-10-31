#ifndef RULES_H
#define RULES_H

#include "entities/player.h"
#include <stdbool.h>

bool rules_can_place_bomb(Player *player);
bool rules_can_kill_player(Player *player);

#endif
