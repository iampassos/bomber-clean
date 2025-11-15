#ifndef RULES_H
#define RULES_H

#include "enemies/enemy.h"
#include "entities/player.h"
#include "entities/power_up.h"
#include <stdbool.h>

bool rules_can_end_game(); // checa se todos os jogadores morreram para terminar o jogo

bool rules_can_place_bomb(Player *player); // checa se o jogador pode colocar uma bomba
bool rules_can_kill_player(Player *player); // checa se o jogador esta invensivel
bool rules_can_spawn_power_up(GridPosition grid);
bool rules_can_kill_power_up(PowerUp *power_up);
bool rules_can_kill_enemy(Enemy *enemy);
bool rules_can_spawn_enemy(GridPosition grid);
bool rules_player_can_consume_power_up(Player *player, PowerUp *power_up);
bool rules_can_spawn_bomb(GridPosition grid);

#endif
