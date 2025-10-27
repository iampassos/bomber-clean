#ifndef STATE_H
#define STATE_H

#include "common.h"
#include "map.h"
#include "player.h"

typedef struct State {
  Map map;
  Player players[MAX_PLAYERS];
  int player_count;
} State;

extern State state;

void state_init();

#endif
